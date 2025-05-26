extends "res://src/enemies/base_enemy.gd"

# Imp specific properties
var can_climb_walls = true
var fireball_damage = 15
var fireball_speed = 200
var fireball_cooldown = 2.0
var can_fire = true

# Preload fireball scene
var fireball_scene = null  # This would be preload("res://src/weapons/fireball.tscn")

func _ready():
	super._ready()
	
	# Set Imp specific values
	enemy_name = "Imp"
	max_health = 40
	health = max_health
	speed = 120
	damage = 10  # Melee damage
	score_value = 100
	
	# Setup timers
	$FireballCooldown.wait_time = fireball_cooldown

func _physics_process(delta):
	super._physics_process(delta)
	
	# Imp specific behavior - wall climbing
	if can_climb_walls and state == States.CHASE:
		# Logic to detect and climb walls would go here
		pass
	
	# Ranged attack behavior
	if state == States.CHASE and can_fire and player:
		var distance_to_player = position.distance_to(player.position)
		
		# If player is in fireball range but not melee range
		if distance_to_player > 50 and distance_to_player < 300:
			# Check if we have line of sight
			var space_state = get_world_2d().direct_space_state
			var query = PhysicsRayQueryParameters2D.create(global_position, player.global_position)
			query.collide_with_areas = true
			query.collide_with_bodies = true
			var result = space_state.intersect_ray(query)
			
			if result and result.collider == player:
				fire_fireball()

func fire_fireball():
	if not can_fire:
		return
	
	# Start cooldown
	can_fire = false
	$FireballCooldown.start()
	
	# Play fireball animation
	$AnimatedSprite2D.play("throw_fireball")
	
	# We'll actually spawn the fireball at the end of the animation
	# via an animation callback, but here's the logic:
	
	# if fireball_scene:
	#     var fireball = fireball_scene.instantiate()
	#     get_tree().get_root().add_child(fireball)
	#     fireball.global_position = global_position
	#     
	#     # Calculate direction to player
	#     var direction = (player.global_position - global_position).normalized()
	#     fireball.set_direction(direction)
	#     fireball.speed = fireball_speed
	#     fireball.damage = fireball_damage

func _on_animation_fireball_spawn_point():
	# This would be called by an animation notification when the
	# fireball throwing animation reaches the right point
	if player:
		# Actual spawn logic would go here if we had the fireball scene
		pass

func _on_FireballCooldown_timeout():
	can_fire = true

func glory_killed():
	# Override with more specific glory kill animations for the Imp
	# For example, ripping off an arm or head
	super.glory_killed()
	
	# Play specific glory kill animation - would be triggered in actual game
	# with multiple animation options
	# match randi() % 3:
	#     0: $AnimatedSprite2D.play("glory_kill_head_rip")
	#     1: $AnimatedSprite2D.play("glory_kill_arm_rip")
	#     2: $AnimatedSprite2D.play("glory_kill_bisection")
