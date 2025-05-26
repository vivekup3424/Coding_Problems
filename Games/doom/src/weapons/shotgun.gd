extends "res://src/weapons/base_weapon.gd"

# Shotgun specific variables
@export var pellet_count = 8
@export var spread_angle = 30  # Degrees

func _ready():
	super._ready()
	weapon_name = "Shotgun"
	damage = 7  # Per pellet
	fire_rate = 0.8
	ammo_type = "shells"
	ammo_per_shot = 1
	magazine_size = 8
	reload_time = 1.5
	current_ammo = magazine_size
	
	# Configure timers
	$FireRateTimer.wait_time = 1.0 / fire_rate
	$ReloadTimer.wait_time = reload_time

func perform_fire():
	print(weapon_name + " fired " + str(pellet_count) + " pellets!")
	
	# Play shotgun sound
	# $ShotgunSound.play()
	
	# Visual effects
	# $MuzzleFlash.show()
	# $MuzzleFlashTimer.start()
	
	# For each pellet, calculate a spread and create a raytrace
	for i in range(pellet_count):
		var random_angle = randf_range(-spread_angle/2, spread_angle/2)
		var direction = Vector2.RIGHT.rotated(deg_to_rad(random_angle))
		
		# If player is facing left, adjust direction
		if player and player.get_node("Sprite2D").flip_h:
			direction.x *= -1
		
		# Create raycast to detect hit
		var space_state = player.get_world_2d().direct_space_state
		var ray_origin = player.global_position
		var ray_end = ray_origin + direction * 500  # Shotgun range
		
		var query = PhysicsRayQueryParameters2D.create(ray_origin, ray_end)
		query.collide_with_areas = true
		query.collide_with_bodies = true
		
		var result = space_state.intersect_ray(query)
		
		if result:
			# Check if we hit an enemy
			if result.collider.is_in_group("enemies"):
				result.collider.take_damage(damage)
				
				# Spawn hit effect at impact point
				# var hit_effect = hit_effect_scene.instantiate()
				# get_tree().get_root().add_child(hit_effect)
				# hit_effect.global_position = result.position
				
	# Camera shake effect
	# player.get_node("Camera2D").apply_shake(0.2, 1.0)

func _on_MuzzleFlashTimer_timeout():
	# $MuzzleFlash.hide()
	pass
