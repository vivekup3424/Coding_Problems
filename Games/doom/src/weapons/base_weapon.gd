extends Node

# Weapon properties
@export var weapon_name = "Base Weapon"
@export var damage = 10
@export var fire_rate = 1.0  # Shots per second
@export var ammo_type = "bullets"
@export var ammo_per_shot = 1
@export var magazine_size = 10
@export var reload_time = 1.0

# Internal state
var current_ammo = 0
var can_fire = true
var is_reloading = false
var player = null

# References
var projectile_scene = null

func _ready():
	current_ammo = magazine_size
	$FireRateTimer.wait_time = 1.0 / fire_rate
	$ReloadTimer.wait_time = reload_time

func set_player(p):
	player = p

func fire():
	if can_fire and current_ammo > 0 and not is_reloading:
		perform_fire()
		current_ammo -= ammo_per_shot
		
		can_fire = false
		$FireRateTimer.start()
		
		# Check if we need to reload
		if current_ammo <= 0:
			reload()
	elif current_ammo <= 0 and not is_reloading:
		reload()

func perform_fire():
	# To be overridden by specific weapon types
	print(weapon_name + " fired!")
	
	# Play sound
	# $AudioStreamPlayer.play()
	
	# Spawn projectile
	# if projectile_scene != null:
	#    var projectile = projectile_scene.instance()
	#    get_tree().get_root().add_child(projectile)
	#    projectile.global_position = global_position
	#    projectile.set_direction(player.facing_direction)

func reload():
	if not is_reloading:
		print(weapon_name + " reloading...")
		is_reloading = true
		$ReloadTimer.start()

func _on_FireRateTimer_timeout():
	can_fire = true

func _on_ReloadTimer_timeout():
	print(weapon_name + " reloaded!")
	current_ammo = magazine_size
	is_reloading = false
	
# Default weapon stats for reference
class Pistol:
	func _init():
		weapon_name = "Pistol"
		damage = 10
		fire_rate = 2.0
		ammo_type = "bullets"
		ammo_per_shot = 1
		magazine_size = 15
		reload_time = 1.0

class Shotgun:
	func _init():
		weapon_name = "Shotgun"
		damage = 7  # Per pellet, typically fires multiple pellets
		fire_rate = 0.8
		ammo_type = "shells"
		ammo_per_shot = 1
		magazine_size = 8
		reload_time = 1.5

class ChainGun:
	func _init():
		weapon_name = "Chain Gun"
		damage = 8
		fire_rate = 8.0  # Very high fire rate
		ammo_type = "bullets"
		ammo_per_shot = 1
		magazine_size = 50
		reload_time = 2.0

class RocketLauncher:
	func _init():
		weapon_name = "Rocket Launcher"
		damage = 50  # High damage with blast radius
		fire_rate = 0.6
		ammo_type = "rockets"
		ammo_per_shot = 1
		magazine_size = 4
		reload_time = 2.5

class BFG:
	func _init():
		weapon_name = "BFG 9000"
		damage = 100  # Extremely high damage
		fire_rate = 0.2  # Very slow fire rate
		ammo_type = "cells"
		ammo_per_shot = 25  # Uses lots of ammo
		magazine_size = 100
		reload_time = 3.0
