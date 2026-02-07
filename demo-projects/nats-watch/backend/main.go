package main

import (
	"database/sql"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"sync"
	"time"

	"github.com/gorilla/websocket"
	_ "github.com/mattn/go-sqlite3"
	"github.com/rs/cors"
)

// Server represents a NATS server configuration
type Server struct {
	ID           int64  `json:"id"`
	Name         string `json:"name"`
	URL          string `json:"url"`
	AuthType     string `json:"auth_type"`
	AuthToken    string `json:"auth_token,omitempty"`
	AuthUsername string `json:"auth_username,omitempty"`
	AuthPassword string `json:"auth_password,omitempty"`
	IsActive     bool   `json:"is_active"`
	CreatedAt    string `json:"created_at"`
	UpdatedAt    string `json:"updated_at"`
}

// LabelCategory represents a custom label category
type LabelCategory struct {
	ID        int64       `json:"id"`
	ServerID  int64       `json:"server_id"`
	Name      string      `json:"name"`
	Rules     []LabelRule `json:"rules,omitempty"`
	CreatedAt string      `json:"created_at"`
	UpdatedAt string      `json:"updated_at"`
}

// LabelRule represents a pattern-based label assignment rule
type LabelRule struct {
	ID         int64  `json:"id"`
	CategoryID int64  `json:"category_id"`
	LabelValue string `json:"label_value"`
	Pattern    string `json:"pattern"`
	Priority   int    `json:"priority"`
	CreatedAt  string `json:"created_at"`
	UpdatedAt  string `json:"updated_at"`
}

// WSMessage represents a WebSocket message
type WSMessage struct {
	Type      string      `json:"type"`
	Timestamp string      `json:"timestamp"`
	Data      interface{} `json:"data"`
}

var (
	db       *sql.DB
	upgrader = websocket.Upgrader{
		CheckOrigin: func(r *http.Request) bool {
			return true // Allow all origins for development
		},
	}
	wsClients   = make(map[*websocket.Conn]bool)
	wsClientsMu sync.Mutex
)

func main() {
	// Initialize database
	initDB()
	defer db.Close()

	// Create router
	mux := http.NewServeMux()

	// Health check
	mux.HandleFunc("/health", healthHandler)

	// Server management
	mux.HandleFunc("/api/servers", serversHandler)
	mux.HandleFunc("/api/servers/", serverHandler)

	// Label management
	mux.HandleFunc("/api/labels", labelsHandler)
	mux.HandleFunc("/api/labels/", labelHandler)
	mux.HandleFunc("/api/rules/", ruleHandler)

	// NATS proxy endpoints
	mux.HandleFunc("/api/proxy/varz", proxyVarzHandler)
	mux.HandleFunc("/api/proxy/connz", proxyConnzHandler)
	mux.HandleFunc("/api/proxy/subz", proxySubzHandler)

	// WebSocket
	mux.HandleFunc("/ws/metrics", wsHandler)

	// CORS middleware
	handler := cors.New(cors.Options{
		AllowedOrigins:   []string{"http://localhost:5173", "http://localhost:3000"},
		AllowedMethods:   []string{"GET", "POST", "PUT", "DELETE", "OPTIONS"},
		AllowedHeaders:   []string{"Content-Type", "Authorization"},
		AllowCredentials: true,
	}).Handler(mux)

	port := os.Getenv("PORT")
	if port == "" {
		port = "8080"
	}

	log.Printf("NATSWatch backend starting on port %s", port)
	log.Fatal(http.ListenAndServe(":"+port, handler))
}

func initDB() {
	var err error
	db, err = sql.Open("sqlite3", "./natswatch.db?_journal_mode=WAL")
	if err != nil {
		log.Fatal(err)
	}

	// Create tables
	schema := `
	CREATE TABLE IF NOT EXISTS servers (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		name TEXT NOT NULL,
		url TEXT NOT NULL,
		auth_type TEXT NOT NULL DEFAULT 'none',
		auth_token TEXT,
		auth_username TEXT,
		auth_password TEXT,
		is_active INTEGER DEFAULT 0,
		created_at TEXT DEFAULT CURRENT_TIMESTAMP,
		updated_at TEXT DEFAULT CURRENT_TIMESTAMP
	);

	CREATE TABLE IF NOT EXISTS label_categories (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		server_id INTEGER NOT NULL,
		name TEXT NOT NULL,
		created_at TEXT DEFAULT CURRENT_TIMESTAMP,
		updated_at TEXT DEFAULT CURRENT_TIMESTAMP,
		FOREIGN KEY (server_id) REFERENCES servers(id) ON DELETE CASCADE
	);

	CREATE TABLE IF NOT EXISTS label_rules (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		category_id INTEGER NOT NULL,
		label_value TEXT NOT NULL,
		pattern TEXT NOT NULL,
		priority INTEGER DEFAULT 0,
		created_at TEXT DEFAULT CURRENT_TIMESTAMP,
		updated_at TEXT DEFAULT CURRENT_TIMESTAMP,
		FOREIGN KEY (category_id) REFERENCES label_categories(id) ON DELETE CASCADE
	);

	CREATE TABLE IF NOT EXISTS client_labels (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		server_id INTEGER NOT NULL,
		client_id TEXT NOT NULL,
		category_id INTEGER NOT NULL,
		label_value TEXT NOT NULL,
		created_at TEXT DEFAULT CURRENT_TIMESTAMP,
		updated_at TEXT DEFAULT CURRENT_TIMESTAMP,
		FOREIGN KEY (server_id) REFERENCES servers(id) ON DELETE CASCADE,
		FOREIGN KEY (category_id) REFERENCES label_categories(id) ON DELETE CASCADE
	);

	CREATE TABLE IF NOT EXISTS alert_rules (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		server_id INTEGER NOT NULL,
		metric TEXT NOT NULL,
		operator TEXT NOT NULL,
		threshold REAL NOT NULL,
		enabled INTEGER DEFAULT 1,
		created_at TEXT DEFAULT CURRENT_TIMESTAMP,
		updated_at TEXT DEFAULT CURRENT_TIMESTAMP,
		FOREIGN KEY (server_id) REFERENCES servers(id) ON DELETE CASCADE
	);
	`

	_, err = db.Exec(schema)
	if err != nil {
		log.Fatal(err)
	}
	log.Println("Database initialized")
}

func healthHandler(w http.ResponseWriter, r *http.Request) {
	json.NewEncoder(w).Encode(map[string]string{"status": "ok"})
}

// Server handlers
func serversHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	switch r.Method {
	case "GET":
		listServers(w, r)
	case "POST":
		createServer(w, r)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func serverHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	// Extract ID from path: /api/servers/{id} or /api/servers/{id}/test or /api/servers/{id}/activate
	path := r.URL.Path[len("/api/servers/"):]

	switch r.Method {
	case "GET":
		getServer(w, r, path)
	case "PUT":
		if len(path) > 0 && path[len(path)-8:] == "activate" {
			activateServer(w, r, path[:len(path)-9])
		} else {
			updateServer(w, r, path)
		}
	case "POST":
		if len(path) > 4 && path[len(path)-4:] == "test" {
			testServer(w, r, path[:len(path)-5])
		} else {
			http.Error(w, "Not found", http.StatusNotFound)
		}
	case "DELETE":
		deleteServer(w, r, path)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func listServers(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query(`SELECT id, name, url, auth_type, is_active, created_at, updated_at FROM servers ORDER BY name`)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	servers := []Server{}
	for rows.Next() {
		var s Server
		var isActive int
		err := rows.Scan(&s.ID, &s.Name, &s.URL, &s.AuthType, &isActive, &s.CreatedAt, &s.UpdatedAt)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		s.IsActive = isActive == 1
		servers = append(servers, s)
	}

	json.NewEncoder(w).Encode(map[string]interface{}{"servers": servers})
}

func createServer(w http.ResponseWriter, r *http.Request) {
	var s Server
	if err := json.NewDecoder(r.Body).Decode(&s); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	if s.AuthType == "" {
		s.AuthType = "none"
	}

	result, err := db.Exec(`
		INSERT INTO servers (name, url, auth_type, auth_token, auth_username, auth_password)
		VALUES (?, ?, ?, ?, ?, ?)
	`, s.Name, s.URL, s.AuthType, s.AuthToken, s.AuthUsername, s.AuthPassword)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	id, _ := result.LastInsertId()
	s.ID = id

	w.WriteHeader(http.StatusCreated)
	json.NewEncoder(w).Encode(s)
}

func getServer(w http.ResponseWriter, r *http.Request, id string) {
	var s Server
	var isActive int
	err := db.QueryRow(`SELECT id, name, url, auth_type, is_active, created_at, updated_at FROM servers WHERE id = ?`, id).
		Scan(&s.ID, &s.Name, &s.URL, &s.AuthType, &isActive, &s.CreatedAt, &s.UpdatedAt)
	if err == sql.ErrNoRows {
		http.Error(w, "Server not found", http.StatusNotFound)
		return
	}
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	s.IsActive = isActive == 1
	json.NewEncoder(w).Encode(s)
}

func updateServer(w http.ResponseWriter, r *http.Request, id string) {
	var s Server
	if err := json.NewDecoder(r.Body).Decode(&s); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	_, err := db.Exec(`
		UPDATE servers SET name = ?, url = ?, auth_type = ?, auth_token = ?, auth_username = ?, auth_password = ?, updated_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`, s.Name, s.URL, s.AuthType, s.AuthToken, s.AuthUsername, s.AuthPassword, id)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	json.NewEncoder(w).Encode(map[string]string{"status": "updated"})
}

func deleteServer(w http.ResponseWriter, r *http.Request, id string) {
	_, err := db.Exec(`DELETE FROM servers WHERE id = ?`, id)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	w.WriteHeader(http.StatusNoContent)
}

func activateServer(w http.ResponseWriter, r *http.Request, id string) {
	// Deactivate all servers first
	_, err := db.Exec(`UPDATE servers SET is_active = 0`)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	// Activate the selected server
	_, err = db.Exec(`UPDATE servers SET is_active = 1 WHERE id = ?`, id)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	json.NewEncoder(w).Encode(map[string]string{"status": "activated"})
}

func testServer(w http.ResponseWriter, r *http.Request, id string) {
	// Get server details
	var s Server
	err := db.QueryRow(`SELECT id, url, auth_type, auth_token, auth_username, auth_password FROM servers WHERE id = ?`, id).
		Scan(&s.ID, &s.URL, &s.AuthType, &s.AuthToken, &s.AuthUsername, &s.AuthPassword)
	if err == sql.ErrNoRows {
		http.Error(w, "Server not found", http.StatusNotFound)
		return
	}
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	// Test connection
	client := &http.Client{Timeout: 5 * time.Second}
	req, _ := http.NewRequest("GET", s.URL+"/varz", nil)
	addAuthHeader(req, s)

	resp, err := client.Do(req)
	if err != nil {
		json.NewEncoder(w).Encode(map[string]interface{}{
			"success": false,
			"error":   err.Error(),
		})
		return
	}
	defer resp.Body.Close()

	if resp.StatusCode != 200 {
		json.NewEncoder(w).Encode(map[string]interface{}{
			"success": false,
			"error":   fmt.Sprintf("HTTP %d", resp.StatusCode),
		})
		return
	}

	var varz map[string]interface{}
	json.NewDecoder(resp.Body).Decode(&varz)

	json.NewEncoder(w).Encode(map[string]interface{}{
		"success":     true,
		"server_name": varz["server_name"],
		"version":     varz["version"],
	})
}

// Label handlers
func labelsHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	serverID := r.URL.Query().Get("server_id")
	if serverID == "" {
		http.Error(w, "server_id required", http.StatusBadRequest)
		return
	}

	switch r.Method {
	case "GET":
		listLabels(w, r, serverID)
	case "POST":
		createLabel(w, r, serverID)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func labelHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	path := r.URL.Path[len("/api/labels/"):]

	switch r.Method {
	case "PUT":
		updateLabel(w, r, path)
	case "DELETE":
		deleteLabel(w, r, path)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func ruleHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	path := r.URL.Path[len("/api/rules/"):]

	switch r.Method {
	case "GET":
		listRules(w, r, path)
	case "POST":
		createRule(w, r, path)
	case "PUT":
		updateRule(w, r, path)
	case "DELETE":
		deleteRule(w, r, path)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func listLabels(w http.ResponseWriter, r *http.Request, serverID string) {
	rows, err := db.Query(`SELECT id, server_id, name, created_at, updated_at FROM label_categories WHERE server_id = ?`, serverID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	categories := []LabelCategory{}
	for rows.Next() {
		var c LabelCategory
		rows.Scan(&c.ID, &c.ServerID, &c.Name, &c.CreatedAt, &c.UpdatedAt)

		// Get rules for this category
		ruleRows, _ := db.Query(`SELECT id, category_id, label_value, pattern, priority FROM label_rules WHERE category_id = ? ORDER BY priority DESC`, c.ID)
		for ruleRows.Next() {
			var rule LabelRule
			ruleRows.Scan(&rule.ID, &rule.CategoryID, &rule.LabelValue, &rule.Pattern, &rule.Priority)
			c.Rules = append(c.Rules, rule)
		}
		ruleRows.Close()

		categories = append(categories, c)
	}

	json.NewEncoder(w).Encode(map[string]interface{}{"categories": categories})
}

func createLabel(w http.ResponseWriter, r *http.Request, serverID string) {
	var c LabelCategory
	json.NewDecoder(r.Body).Decode(&c)

	result, err := db.Exec(`INSERT INTO label_categories (server_id, name) VALUES (?, ?)`, serverID, c.Name)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	id, _ := result.LastInsertId()
	c.ID = id
	w.WriteHeader(http.StatusCreated)
	json.NewEncoder(w).Encode(c)
}

func updateLabel(w http.ResponseWriter, r *http.Request, id string) {
	var c LabelCategory
	json.NewDecoder(r.Body).Decode(&c)

	_, err := db.Exec(`UPDATE label_categories SET name = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?`, c.Name, id)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	json.NewEncoder(w).Encode(map[string]string{"status": "updated"})
}

func deleteLabel(w http.ResponseWriter, r *http.Request, id string) {
	db.Exec(`DELETE FROM label_categories WHERE id = ?`, id)
	w.WriteHeader(http.StatusNoContent)
}

func listRules(w http.ResponseWriter, r *http.Request, categoryID string) {
	rows, err := db.Query(`SELECT id, category_id, label_value, pattern, priority FROM label_rules WHERE category_id = ? ORDER BY priority DESC`, categoryID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	rules := []LabelRule{}
	for rows.Next() {
		var rule LabelRule
		rows.Scan(&rule.ID, &rule.CategoryID, &rule.LabelValue, &rule.Pattern, &rule.Priority)
		rules = append(rules, rule)
	}
	json.NewEncoder(w).Encode(map[string]interface{}{"rules": rules})
}

func createRule(w http.ResponseWriter, r *http.Request, categoryID string) {
	var rule LabelRule
	json.NewDecoder(r.Body).Decode(&rule)

	result, err := db.Exec(`INSERT INTO label_rules (category_id, label_value, pattern, priority) VALUES (?, ?, ?, ?)`,
		categoryID, rule.LabelValue, rule.Pattern, rule.Priority)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	id, _ := result.LastInsertId()
	rule.ID = id
	w.WriteHeader(http.StatusCreated)
	json.NewEncoder(w).Encode(rule)
}

func updateRule(w http.ResponseWriter, r *http.Request, id string) {
	var rule LabelRule
	json.NewDecoder(r.Body).Decode(&rule)

	_, err := db.Exec(`UPDATE label_rules SET label_value = ?, pattern = ?, priority = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?`,
		rule.LabelValue, rule.Pattern, rule.Priority, id)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	json.NewEncoder(w).Encode(map[string]string{"status": "updated"})
}

func deleteRule(w http.ResponseWriter, r *http.Request, id string) {
	db.Exec(`DELETE FROM label_rules WHERE id = ?`, id)
	w.WriteHeader(http.StatusNoContent)
}

// NATS Proxy handlers
func getActiveServer() (*Server, error) {
	var s Server
	err := db.QueryRow(`SELECT id, url, auth_type, auth_token, auth_username, auth_password FROM servers WHERE is_active = 1`).
		Scan(&s.ID, &s.URL, &s.AuthType, &s.AuthToken, &s.AuthUsername, &s.AuthPassword)
	return &s, err
}

func addAuthHeader(req *http.Request, s Server) {
	switch s.AuthType {
	case "token":
		req.Header.Set("Authorization", "token "+s.AuthToken)
	case "userpass":
		auth := base64.StdEncoding.EncodeToString([]byte(s.AuthUsername + ":" + s.AuthPassword))
		req.Header.Set("Authorization", "Basic "+auth)
	}
}

func proxyVarzHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	server, err := getActiveServer()
	if err != nil {
		http.Error(w, "No active server configured", http.StatusBadRequest)
		return
	}

	client := &http.Client{Timeout: 5 * time.Second}
	req, _ := http.NewRequest("GET", server.URL+"/varz", nil)
	addAuthHeader(req, *server)

	resp, err := client.Do(req)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadGateway)
		return
	}
	defer resp.Body.Close()

	io.Copy(w, resp.Body)
}

func proxyConnzHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	server, err := getActiveServer()
	if err != nil {
		http.Error(w, "No active server configured", http.StatusBadRequest)
		return
	}

	client := &http.Client{Timeout: 10 * time.Second}
	req, _ := http.NewRequest("GET", server.URL+"/connz?subs=detail", nil)
	addAuthHeader(req, *server)

	resp, err := client.Do(req)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadGateway)
		return
	}
	defer resp.Body.Close()

	io.Copy(w, resp.Body)
}

func proxySubzHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	server, err := getActiveServer()
	if err != nil {
		http.Error(w, "No active server configured", http.StatusBadRequest)
		return
	}

	client := &http.Client{Timeout: 10 * time.Second}
	req, _ := http.NewRequest("GET", server.URL+"/subz?subs=1", nil)
	addAuthHeader(req, *server)

	resp, err := client.Do(req)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadGateway)
		return
	}
	defer resp.Body.Close()

	io.Copy(w, resp.Body)
}

// WebSocket handler
func wsHandler(w http.ResponseWriter, r *http.Request) {
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println("WebSocket upgrade error:", err)
		return
	}

	wsClientsMu.Lock()
	wsClients[conn] = true
	wsClientsMu.Unlock()

	defer func() {
		wsClientsMu.Lock()
		delete(wsClients, conn)
		wsClientsMu.Unlock()
		conn.Close()
	}()

	// Start polling and sending data
	ticker := time.NewTicker(5 * time.Second)
	defer ticker.Stop()

	// Send initial data
	sendMetrics(conn)

	for {
		select {
		case <-ticker.C:
			sendMetrics(conn)
		}
	}
}

func sendMetrics(conn *websocket.Conn) {
	server, err := getActiveServer()
	if err != nil {
		return
	}

	client := &http.Client{Timeout: 5 * time.Second}

	// Fetch varz
	req, _ := http.NewRequest("GET", server.URL+"/varz", nil)
	addAuthHeader(req, *server)
	resp, err := client.Do(req)
	if err == nil {
		var data interface{}
		json.NewDecoder(resp.Body).Decode(&data)
		resp.Body.Close()

		msg := WSMessage{
			Type:      "varz",
			Timestamp: time.Now().UTC().Format(time.RFC3339),
			Data:      data,
		}
		conn.WriteJSON(msg)
	}

	// Fetch connz
	req, _ = http.NewRequest("GET", server.URL+"/connz?subs=detail", nil)
	addAuthHeader(req, *server)
	resp, err = client.Do(req)
	if err == nil {
		var data interface{}
		json.NewDecoder(resp.Body).Decode(&data)
		resp.Body.Close()

		msg := WSMessage{
			Type:      "connz",
			Timestamp: time.Now().UTC().Format(time.RFC3339),
			Data:      data,
		}
		conn.WriteJSON(msg)
	}

	// Fetch subz
	req, _ = http.NewRequest("GET", server.URL+"/subz?subs=1", nil)
	addAuthHeader(req, *server)
	resp, err = client.Do(req)
	if err == nil {
		var data interface{}
		json.NewDecoder(resp.Body).Decode(&data)
		resp.Body.Close()

		msg := WSMessage{
			Type:      "subz",
			Timestamp: time.Now().UTC().Format(time.RFC3339),
			Data:      data,
		}
		conn.WriteJSON(msg)
	}
}
