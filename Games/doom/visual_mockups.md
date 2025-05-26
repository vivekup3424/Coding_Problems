# Visual Mockups - 2D Doom Platformer

## Player Character Concept

The Doom Slayer would be represented as a detailed pixel art character with the following animations:
- Idle stance (breathing animation)
- Running
- Jumping/Double jumping
- Weapon firing (for each weapon)
- Glory kill animations (2-3 variations)
- Death animation

```
  _____
 /     \
 | o o |
 \_____/
  |   |
 /|___|\ [Weapon]
/ |   | \
  |   |
  |   |
 /     \
/       \
```
(ASCII art is placeholder for actual pixel art design)

## Level Layout Example

### Hell Portal Level
```
                    [Secret Area]
                        |
                    ____|____
                   /         \
                  /           \
 [Start]________/             \_______________[Exit Portal]
       |                                      |
       |                                      |
       |____[Lava Pit]_____[Health Pickup]____|
                      \                  /
                       \________________/
                           [Boss Area]
```

## Enemy Design Concepts

### Imp
- Small, agile enemies that throw fireballs
- Can climb walls
- Quick melee attack when close

### Cacodemon
- Floating enemy that follows player
- Shoots projectiles in arc
- Vulnerable mouth that opens before attack
- Glory kill: Player jumps into mouth and bursts it from inside

### Cyberdemon (Boss)
- Large sprite that takes up 1/4 of the screen height
- Multiple attack patterns:
  - Stomp (creates shockwave player must jump over)
  - Missile barrage
  - Charge attack
- Weak points that light up during certain attacks
- Progressive damage model (shows battle damage as health decreases)

## Weapon Visual Effects

### Shotgun
- Short range spread pattern
- Visible pellet impacts
- Powerful knockback effect on enemies
- Shell ejection animation

### BFG
- Charge up animation with green glow
- Screen-shaking discharge
- Green tendrils that seek out enemies
- Explosion effects on impact

## HUD Design
```
┌────────────────────────────────────────────────────────┐
│ HEALTH: ███████████ 100  |  ARMOR: ██████████ 100     │
│                                                       │
│ AMMO: 24/48  |  WEAPON: SHOTGUN  |  SCORE: 000,000    │
└────────────────────────────────────────────────────────┘
```

## Art Direction References
- Color palette: Limited color scheme with emphasis on reds, oranges, and dark grays
- Lighting: Dynamic lighting effects even in 2D space
- Particle effects: For weapon impacts, explosions, and gore
- Environmental storytelling: Destroyed labs, pentagram symbols, etc.

## Animation Style
- Fluid, high frame rate animations for the player character
- Exaggerated enemy death animations
- Weapon recoil and reload animations
- Environmental animations (lava bubbling, flickering lights)
