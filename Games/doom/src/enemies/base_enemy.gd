extends CharacterBody2D

# Enemy properties
@export var enemy_name = "Base Enemy"
@export var max_health = 50
@export var speed = 100
@export var damage = 10
@export var score_value = 100

# State variables
var health
var state = States.IDLE
var staggered = false
var target = null
var path = []
var path_index = 0

# References
var player = null

# Enums
enum States {IDLE, PATROL, CHASE, ATTACK, STAGGERED, DYING}

func _ready():
	health = max_health
	add_to_group("enemies")
	
	# Get reference to player
	player = get_tree().get_nodes_in_group("player")[0]
	
	# Setup animation
	$AnimatedSprite2D.play("idle")

func _physics_process(delta):
	match state:
		States.IDLE:
			process_idle_state(delta)
		States.PATROL:
			process_patrol_state(delta)
		States.CHASE:
			process_chase_state(delta)
		States.ATTACK:
			process_attack_state(delta)
		States.STAGGERED:
			process_staggered_state(delta)
		States.DYING:
			process_dying_state(delta)

func process_idle_state(_delta):
	# Check for player in detection range
	if player and position.distance_to(player.position) < 300:
		set_state(States.CHASE)
	
	# Randomly decide to patrol
	if randf() < 0.01:  # 1% chance per frame to start patrolling
		set_state(States.PATROL)
		setup_patrol_path()

func process_patrol_state(delta):
	# Move along patrol path
	if path.size() > 0 and path_index < path.size():
		var direction = (path[path_index] - position).normalized()
		velocity = direction * speed
		move_and_slide()
		
		# Check if we're close to the next patrol point
		if position.distance_to(path[path_index]) < 10:
			path_index += 1
			
			# If we reached the end of the path, go back to idle
			if path_index >= path.size():
				set_state(States.IDLE)
	
	# Check for player in detection range
	if player and position.distance_to(player.position) < 300:
		set_state(States.CHASE)

func process_chase_state(delta):
	# Chase player
	if player:
		var direction = (player.position - position).normalized()
		velocity = direction * speed
		move_and_slide()
		
		# Face the right direction
		$Sprite2D.flip_h = (direction.x < 0)
		
		# Check if close enough to attack
		if position.distance_to(player.position) < 50:
			set_state(States.ATTACK)
			$AttackTimer.start()
			
		# If player is too far, go back to idle
		if position.distance_to(player.position) > 500:
			set_state(States.IDLE)

func process_attack_state(_delta):
	# Attack animation plays, damage happens in _on_AttackTimer_timeout
	pass

func process_staggered_state(_delta):
	# Enemy is staggered and vulnerable to glory kill
	if not staggered:
		add_to_group("staggered")
		staggered = true
		$StaggerTimer.start()

func process_dying_state(_delta):
	# Death animation plays
	# When animation finishes, the enemy will be removed
	pass

func set_state(new_state):
	state = new_state
	
	# Play appropriate animation
	match state:
		States.IDLE:
			$AnimatedSprite2D.play("idle")
		States.PATROL:
			$AnimatedSprite2D.play("walk")
		States.CHASE:
			$AnimatedSprite2D.play("walk")
		States.ATTACK:
			$AnimatedSprite2D.play("attack")
		States.STAGGERED:
			$AnimatedSprite2D.play("staggered")
		States.DYING:
			$AnimatedSprite2D.play("death")

func setup_patrol_path():
	# In a real implementation, this would get waypoints from the level
	# For now, just create a simple path around the current position
	path = []
	path.append(position + Vector2(100, 0))
	path.append(position + Vector2(100, 100))
	path.append(position + Vector2(0, 100))
	path.append(position)
	path_index = 0

func take_damage(amount):
	health -= amount
	
	# Visual feedback
	$AnimatedSprite2D.modulate = Color(1, 0.3, 0.3)
	$DamageColorTimer.start()
	
	# Check for stagger or death
	if health <= 0:
		die()
	elif health < max_health * 0.3:  # Stagger at 30% health
		set_state(States.STAGGERED)

func die():
	# Enter dying state
	set_state(States.DYING)
	
	# Remove from physics processing
	set_physics_process(false)
	remove_from_group("enemies")
	remove_from_group("staggered")
	
	# Add score
	# get_node("/root/GameManager").add_score(score_value)
	
	# Queue for deletion after death animation
	$DieTimer.start()

func glory_killed():
	# Special death for glory kills
	$AnimatedSprite2D.play("glory_kill_death")
	die()
	
	# Spawn health or ammo pickup
	if randf() < 0.5:
		spawn_health_pickup()
	else:
		spawn_ammo_pickup()

func spawn_health_pickup():
	# Instantiate health pickup
	# var health_pickup = health_pickup_scene.instantiate()
	# get_parent().add_child(health_pickup)
	# health_pickup.global_position = global_position
	pass

func spawn_ammo_pickup():
	# Instantiate ammo pickup
	# var ammo_pickup = ammo_pickup_scene.instantiate()
	# get_parent().add_child(ammo_pickup)
	# ammo_pickup.global_position = global_position
	pass

func _on_AttackTimer_timeout():
	# Deal damage to player if still in range
	if player and position.distance_to(player.position) < 50:
		player.take_damage(damage)
		
	# Return to chase state
	set_state(States.CHASE)

func _on_DamageColorTimer_timeout():
	$AnimatedSprite2D.modulate = Color(1, 1, 1)  # Reset to normal color

func _on_StaggerTimer_timeout():
	# Remove from staggered group if still alive
	remove_from_group("staggered")
	staggered = false
	
	# Return to chase state if still alive
	if health > 0:
		set_state(States.CHASE)

func _on_DieTimer_timeout():
	queue_free()  # Remove enemy
