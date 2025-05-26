extends Node2D

func _ready():
	# This script is attached to the main.tscn scene
	# It serves as the entry point for the game
	
	# Get reference to game manager
	var game_manager = get_node("/root/GameManager")
	if game_manager:
		# Show the main menu when the game starts
		game_manager.show_main_menu()
	
	# Setup input processing
	setup_input_map()

func setup_input_map():
	# This ensures that the input map is correctly set up
	# Normally this would be done in project settings, but this is a backup
	
	if not InputMap.has_action("move_left"):
		InputMap.add_action("move_left")
		var event = InputEventKey.new()
		event.keycode = KEY_A
		InputMap.action_add_event("move_left", event)
		
		event = InputEventKey.new()
		event.keycode = KEY_LEFT
		InputMap.action_add_event("move_left", event)
	
	if not InputMap.has_action("move_right"):
		InputMap.add_action("move_right")
		var event = InputEventKey.new()
		event.keycode = KEY_D
		InputMap.action_add_event("move_right", event)
		
		event = InputEventKey.new()
		event.keycode = KEY_RIGHT
		InputMap.action_add_event("move_right", event)
	
	if not InputMap.has_action("jump"):
		InputMap.add_action("jump")
		var event = InputEventKey.new()
		event.keycode = KEY_SPACE
		InputMap.action_add_event("jump", event)
		
		event = InputEventKey.new()
		event.keycode = KEY_W
		InputMap.action_add_event("jump", event)
		
		event = InputEventKey.new()
		event.keycode = KEY_UP
		InputMap.action_add_event("jump", event)

func _input(event):
	# Handle global input like screenshot capture
	if event is InputEventKey:
		if event.pressed and event.keycode == KEY_F12:
			# Take a screenshot
			var datetime = Time.get_datetime_string_from_system(false, true).replace(":", "-")
			var screenshot_path = "user://screenshot_" + datetime + ".png"
			var image = get_viewport().get_texture().get_image()
			image.save_png(screenshot_path)
			print("Screenshot saved to: " + screenshot_path)
