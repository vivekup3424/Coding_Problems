#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_PENDING_CONNECTIONS 3

void debug_socket_address(struct sockaddr_in *address) {
    printf("\nSocket Address Details:");
    printf("\n----------------------");
    printf("\nIP Address: %s", inet_ntoa(address->sin_addr));
    printf("\nPort: %d", ntohs(address->sin_port));
    printf("\nAddress Family: %d\n", address->sin_family);
}

int main(int argc, char *argv[]) {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int opt = 1;
    
    printf("\n[DEBUG] Starting server initialization...\n");

    // 1. Create a socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("[ERROR] Server socket creation failed");
        printf("[DEBUG] Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    printf("[SUCCESS] Server socket created with FD: %d\n", server_fd);

    // Get and display hostname
    char hostname[BUFFER_SIZE];
    if (gethostname(hostname, BUFFER_SIZE) != 0) {
        perror("[ERROR] Failed to get hostname");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("[INFO] Hostname: %s\n", hostname);

    // Set socket options to reuse address and port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("[ERROR] Failed to set socket options");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("[DEBUG] Socket options set successfully\n");

    // Initialize address structure
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    debug_socket_address(&address);

    // 2. Bind socket to address and port
    if (bind(server_fd, (struct sockaddr*)&address, addrlen) < 0) {
        perror("[ERROR] Bind failed");
        printf("[DEBUG] Error code: %d\n", errno);
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("[SUCCESS] Socket bound successfully\n");

    // 3. Listen for connections
    if (listen(server_fd, MAX_PENDING_CONNECTIONS) < 0) {
        perror("[ERROR] Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("[INFO] Server is listening on %s:%d\n", hostname, PORT);
    printf("[DEBUG] Maximum pending connections: %d\n", MAX_PENDING_CONNECTIONS);

    // 4. Accept and handle connections
    printf("[DEBUG] Waiting for incoming connections...\n");
    
    while(1) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("[ERROR] Accept failed");
            continue;
        }

        printf("[SUCCESS] New connection accepted\n");
        printf("[DEBUG] Client IP: %s\n", inet_ntoa(address.sin_addr));
        printf("[DEBUG] Client Port: %d\n", ntohs(address.sin_port));

        // Read incoming message
        ssize_t bytes_read = read(new_socket, buffer, BUFFER_SIZE);
        if (bytes_read > 0) {
            printf("[DEBUG] Received %zd bytes\n", bytes_read);
            printf("[INFO] Message from client: %s\n", buffer);

            // Send response
            const char *response = "Message received successfully\n";
            send(new_socket, response, strlen(response), 0);
            printf("[DEBUG] Response sent to client\n");
        }

        // Clear buffer for next message
        memset(buffer, 0, BUFFER_SIZE);
        
        // Close client socket
        close(new_socket);
        printf("[DEBUG] Connection closed\n\n");
    }

    // Close server socket (this part is never reached in this example)
    close(server_fd);
    return 0;
}
