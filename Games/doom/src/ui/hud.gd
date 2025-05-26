extends CanvasLayer

# References to UI elements
@onready var health_bar = $BottomPanel/HealthBar
@onready var armor_bar = $BottomPanel/ArmorBar
@onready var weapon_label = $BottomPanel/WeaponInfo/WeaponName
@onready var ammo_label = $BottomPanel/WeaponInfo/AmmoCount
@onready var score_label = $TopPanel/ScoreValue
@onready var objective_label = $TopPanel/ObjectiveText

func _ready():
	# Set initial values
	update_health(100)
	update_armor(0)
	update_score(0)
	update_weapon("Pistol", "∞")  # Pistol usually has unlimited ammo
	set_objective("Find the exit")

func update_health(value):
	# Update health bar and text
	health_bar.value = value
	$BottomPanel/HealthLabel.text = str(value)
	
	# Visual indication when health is low
	if value < 30:
		$BottomPanel/HealthLabel.modulate = Color(1, 0, 0)  # Red
		# Add pulsing animation
		if not $PulseAnimation.is_playing():
			$PulseAnimation.play("pulse_health_low")
	else:
		$BottomPanel/HealthLabel.modulate = Color(1, 1, 1)  # White
		if $PulseAnimation.is_playing():
			$PulseAnimation.stop()

func update_armor(value):
	# Update armor bar and text
	armor_bar.value = value
	$BottomPanel/ArmorLabel.text = str(value)

func update_score(value):
	# Update score text
	score_label.text = str(value)

func update_weapon(weapon_name, ammo_count):
	# Update weapon info
	weapon_label.text = weapon_name
	ammo_label.text = str(ammo_count)
	
	# Show the icon for the current weapon
	update_weapon_icon(weapon_name)

func update_weapon_icon(weapon_name):
	# Hide all weapon icons
	for icon in $BottomPanel/WeaponInfo/Icons.get_children():
		icon.visible = false
	
	# Show the relevant weapon icon
	match weapon_name:
		"Pistol":
			$BottomPanel/WeaponInfo/Icons/PistolIcon.visible = true
		"Shotgun":
			$BottomPanel/WeaponInfo/Icons/ShotgunIcon.visible = true
		"Chain Gun":
			$BottomPanel/WeaponInfo/Icons/ChaingunIcon.visible = true
		"Rocket Launcher":
			$BottomPanel/WeaponInfo/Icons/RocketLauncherIcon.visible = true
		"BFG 9000":
			$BottomPanel/WeaponInfo/Icons/BFGIcon.visible = true

func set_objective(text):
	# Set current objective
	objective_label.text = text
	
	# Show notification animation
	$ObjectiveAnimation.play("show_objective")

func show_damage_indicator():
	# Flash the screen red when player takes damage
	$DamageIndicator.modulate.a = 0.5  # Set opacity
	$DamageAnimation.play("damage_flash")

func show_pickup_message(pickup_type, amount):
	# Show a temporary message for pickups
	var message = ""
	match pickup_type:
		"health":
			message = "Health +" + str(amount)
		"armor":
			message = "Armor +" + str(amount)
		"ammo":
			message = "Ammo +" + str(amount)
		"weapon":
			message = "New weapon: " + amount
	
	$PickupMessage.text = message
	$PickupAnimation.play("show_pickup")

func update_enemy_counter(current, total):
	$TopPanel/EnemyCount.text = str(current) + "/" + str(total) + " Enemies"

func update_secrets_counter(current, total):
	$TopPanel/SecretCount.text = str(current) + "/" + str(total) + " Secrets"

func show_boss_health_bar(boss_name):
	$BossHealthBar.visible = true
	$BossHealthBar/BossName.text = boss_name
	$BossBarAnimation.play("show_boss_bar")

func update_boss_health(percentage):
	$BossHealthBar/Bar.value = percentage
	
	# Change color based on health
	if percentage < 30:
		$BossHealthBar/Bar.modulate = Color(1, 0, 0)  # Red
	elif percentage < 60:
		$BossHealthBar/Bar.modulate = Color(1, 1, 0)  # Yellow
	else:
		$BossHealthBar/Bar.modulate = Color(1, 1, 1)  # White

func hide_boss_health_bar():
	$BossBarAnimation.play_backwards("show_boss_bar")
	yield($BossBarAnimation, "animation_finished")
	$BossHealthBar.visible = false
