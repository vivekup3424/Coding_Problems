extends Node2D

# Level properties
@export var level_name = "Level 1"
@export var next_level = "res://src/levels/level2.tscn"
@export var background_music = "res://assets/music/level1.ogg"

# Level state
var secrets_found = 0
var total_secrets = 3
var enemies_killed = 0
var total_enemies = 0
var level_completed = false

# Signal for level completion
signal level_completed()

func _ready():
	# Set up the level
	setup_level()
	
	# Connect signals from player, enemies, etc.
	connect_signals()
	
	# Start background music
	# $BackgroundMusic.stream = load(background_music)
	# $BackgroundMusic.play()
	
	# Count total enemies
	total_enemies = get_tree().get_nodes_in_group("enemies").size()

func setup_level():
	# Place player at spawn point
	var player = get_tree().get_nodes_in_group("player")[0]
	var spawn_point = $SpawnPoint
	if player and spawn_point:
		player.global_position = spawn_point.global_position
	
	# Setup exit door/trigger
	# $ExitDoor.connect("player_reached_exit", self, "_on_player_reached_exit")

func connect_signals():
	# Listen for enemy death signals to count kills
	var enemies = get_tree().get_nodes_in_group("enemies")
	for enemy in enemies:
		if enemy.has_signal("enemy_killed"):
			enemy.connect("enemy_killed", _on_enemy_killed)
	
	# Listen for secret area discoveries
	var secret_areas = get_tree().get_nodes_in_group("secret_areas")
	for area in secret_areas:
		if area.has_signal("secret_found"):
			area.connect("secret_found", _on_secret_found)

func _on_enemy_killed():
	enemies_killed += 1
	
	# Check if all enemies are defeated
	check_level_progress()
	
	# Update HUD if needed
	# $HUD.update_enemy_counter(enemies_killed, total_enemies)

func _on_secret_found():
	secrets_found += 1
	
	# Update HUD if needed
	# $HUD.update_secrets_counter(secrets_found, total_secrets)

func _on_player_reached_exit():
	if not level_completed:
		level_completed = true
		
		# Calculate completion percentage
		var kill_percentage = float(enemies_killed) / total_enemies * 100
		var secret_percentage = float(secrets_found) / total_secrets * 100
		
		# Show level completion screen with stats
		# $LevelCompletionScreen.show_stats(kill_percentage, secret_percentage)
		# $LevelCompletionScreen.show()
		
		# Emit level completed signal
		emit_signal("level_completed")
		
		# Wait for player to press a button to continue
		# $LevelCompletionScreen.connect("continue_pressed", self, "_on_continue_to_next_level")

func _on_continue_to_next_level():
	# Get the game manager to load the next level
	var game_manager = get_node("/root/GameManager")
	if game_manager:
		game_manager.next_level()

func check_level_progress():
	# Check if the level should progress (e.g., open doors after killing certain enemies)
	# This can be customized based on level design
	
	# Example: If 50% of enemies are killed, open a specific door
	if enemies_killed >= total_enemies * 0.5:
		# $MidLevelDoor.open()
		pass
