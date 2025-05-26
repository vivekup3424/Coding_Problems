extends CharacterBody2D

# Player movement variables
@export var speed = 300.0
@export var jump_force = -600.0
@export var double_jump_force = -450.0
@export var gravity = 1200.0

# Player status variables
var can_double_jump = true
var health = 100
var armor = 0
var max_health = 100
var max_armor = 100

# Weapon system
var current_weapon_index = 0
var weapons = []

# State variables
var is_glory_kill_available = false
var glory_kill_target = null

func _ready():
	# Initialize weapons
	initialize_weapons()

func _physics_process(delta):
	# Apply gravity
	if not is_on_floor():
		velocity.y += gravity * delta
	
	# Handle jump
	if Input.is_action_just_pressed("jump"):
		if is_on_floor():
			velocity.y = jump_force
			can_double_jump = true
		elif can_double_jump:
			velocity.y = double_jump_force
			can_double_jump = false
	
	# Get horizontal movement direction
	var direction = Input.get_axis("move_left", "move_right")
	velocity.x = direction * speed
	
	# Face the right direction
	if direction != 0:
		$Sprite2D.flip_h = (direction < 0)
	
	# Apply movement
	move_and_slide()
	
	# Handle weapon firing
	if Input.is_action_pressed("fire"):
		fire_weapon()
	
	# Handle weapon switching
	if Input.is_action_just_pressed("next_weapon"):
		cycle_weapon(1)
	if Input.is_action_just_pressed("prev_weapon"):
		cycle_weapon(-1)
	
	# Handle glory kill
	if Input.is_action_just_pressed("glory_kill") and is_glory_kill_available:
		perform_glory_kill()

func initialize_weapons():
	# This will be populated with actual weapon instances
	weapons = []
	current_weapon_index = 0
	
	# Example call to add weapons
	# add_weapon(preload("res://src/weapons/pistol.gd").new())
	# add_weapon(preload("res://src/weapons/shotgun.gd").new())

func add_weapon(weapon):
	weapons.append(weapon)
	weapon.set_player(self)

func cycle_weapon(direction):
	if weapons.size() > 0:
		current_weapon_index = (current_weapon_index + direction) % weapons.size()
		if current_weapon_index < 0:
			current_weapon_index = weapons.size() - 1
		
		# Update HUD
		emit_signal("weapon_changed", current_weapon_index, weapons[current_weapon_index])

func fire_weapon():
	if weapons.size() > 0 and current_weapon_index < weapons.size():
		weapons[current_weapon_index].fire()

func take_damage(amount):
	# First apply damage to armor if available
	var remaining_damage = amount
	if armor > 0:
		if armor >= remaining_damage:
			armor -= remaining_damage
			remaining_damage = 0
		else:
			remaining_damage -= armor
			armor = 0
	
	# Apply remaining damage to health
	if remaining_damage > 0:
		health -= remaining_damage
		
		# Check for death
		if health <= 0:
			health = 0
			die()
			
	# Update HUD
	emit_signal("health_changed", health, armor)

func heal(amount):
	health = min(health + amount, max_health)
	emit_signal("health_changed", health, armor)

func add_armor(amount):
	armor = min(armor + amount, max_armor)
	emit_signal("health_changed", health, armor)

func check_for_glory_kills():
	# This will be implemented to check for nearby enemies that are staggered
	var staggered_enemies = get_tree().get_nodes_in_group("staggered")
	
	is_glory_kill_available = false
	glory_kill_target = null
	
	for enemy in staggered_enemies:
		var distance = global_position.distance_to(enemy.global_position)
		if distance < 100:  # Glory kill range
			is_glory_kill_available = true
			glory_kill_target = enemy
			break

func perform_glory_kill():
	if glory_kill_target:
		# Play glory kill animation
		# glory_kill_target.glory_killed()
		
		# Player gets health bonus
		heal(10)
		
		# Reset glory kill state
		is_glory_kill_available = false
		glory_kill_target = null

func die():
	# Game over logic
	print("Player died")
	# get_tree().reload_current_scene()

# Signals
signal health_changed(health, armor)
signal weapon_changed(index, weapon)
