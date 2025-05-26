extends Node2D

# Game states
enum GameState {MENU, PLAYING, PAUSED, GAME_OVER}
var current_state = GameState.MENU

# Game progress variables
var score = 0
var current_level = 0
var levels = [
	"res://src/levels/level1.tscn",
	"res://src/levels/level2.tscn",
	"res://src/levels/level3.tscn"
]

# Player reference
var player = null

func _ready():
	# Start with the main menu
	show_main_menu()

func _process(delta):
	match current_state:
		GameState.MENU:
			# Menu logic handled by the menu scene
			pass
		GameState.PLAYING:
			# Game is running normally
			update_hud()
		GameState.PAUSED:
			# Game is paused
			if Input.is_action_just_pressed("pause"):
				unpause_game()
		GameState.GAME_OVER:
			# Game over screen logic
			if Input.is_action_just_pressed("restart"):
				restart_game()

func show_main_menu():
	current_state = GameState.MENU
	
	# Load and display the main menu scene
	# var menu_scene = preload("res://src/ui/main_menu.tscn").instantiate()
	# add_child(menu_scene)

func start_new_game():
	# Reset game variables
	score = 0
	current_level = 0
	
	# Start first level
	load_level(current_level)
	
	# Set game state to playing
	current_state = GameState.PLAYING

func load_level(level_index):
	# Remove current level if any
	var current_level_node = get_node_or_null("Level")
	if current_level_node:
		current_level_node.queue_free()
	
	# Load and instantiate the new level
	if level_index < levels.size():
		# Here we would load the level scene
		# var level_scene = load(levels[level_index]).instantiate()
		# level_scene.name = "Level"
		# add_child(level_scene)
		
		# Get player reference
		# player = get_tree().get_nodes_in_group("player")[0]
		
		print("Loading level " + str(level_index + 1))
	else:
		# No more levels, player won the game
		game_won()

func next_level():
	current_level += 1
	load_level(current_level)

func update_hud():
	if player:
		# Update score, health, armor, ammo display
		# $HUD.update_health(player.health)
		# $HUD.update_armor(player.armor)
		# $HUD.update_score(score)
		
		# Update weapon display
		if player.weapons.size() > 0 and player.current_weapon_index < player.weapons.size():
			var current_weapon = player.weapons[player.current_weapon_index]
			# $HUD.update_weapon(current_weapon.weapon_name, current_weapon.current_ammo)
			pass

func pause_game():
	if current_state == GameState.PLAYING:
		current_state = GameState.PAUSED
		get_tree().paused = true
		
		# Show pause menu
		# $PauseMenu.show()

func unpause_game():
	if current_state == GameState.PAUSED:
		current_state = GameState.PLAYING
		get_tree().paused = false
		
		# Hide pause menu
		# $PauseMenu.hide()

func game_over():
	current_state = GameState.GAME_OVER
	
	# Show game over screen
	# var game_over_screen = preload("res://src/ui/game_over.tscn").instantiate()
	# add_child(game_over_screen)

func game_won():
	current_state = GameState.GAME_OVER
	
	# Show victory screen
	# var victory_screen = preload("res://src/ui/victory.tscn").instantiate()
	# add_child(victory_screen)

func restart_game():
	# Reset everything and start a new game
	get_tree().reload_current_scene()

func add_score(points):
	score += points
	# $HUD.update_score(score)

func _input(event):
	if event.is_action_pressed("pause") and current_state == GameState.PLAYING:
		pause_game()
	elif event.is_action_pressed("pause") and current_state == GameState.PAUSED:
		unpause_game()
