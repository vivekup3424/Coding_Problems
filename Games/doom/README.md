# Doom 2D Platformer

A 2D platformer adaptation of the classic Doom, featuring fast-paced combat, iconic weapons, and demonic enemies in a side-scrolling format.

## Features

- Classic Doom weapons: Pistol, Shotgun, Chain Gun, Rocket Launcher, and BFG 9000
- Recognizable enemies from Doom adapted to 2D gameplay
- Glory kill mechanics for health/ammo replenishment
- Fluid platforming mechanics with running, jumping, and double jumping
- Multiple levels with secrets, hazards, and boss encounters

## Installation and Setup

### Prerequisites

- [Godot Engine 4.0+](https://godotengine.org/)
- Basic understanding of 2D platformer controls

### Installation Steps

1. Clone or download this repository
   ```
   git clone https://github.com/yourusername/doom-2d-platformer.git
   ```

2. Open Godot Engine
   
3. Import the project
   - Click "Import"
   - Navigate to the downloaded repository
   - Select the `project.godot` file
   - Click "Import & Edit"

4. Run the game
   - Once the project is open in the Godot editor, click the "Play" button in the top-right corner

## How to Play

### Controls

- **WASD** or **Arrow Keys**: Move left/right, look up/down
- **Space**: Jump (press twice for double jump)
- **Mouse 1**: Fire weapon
- **F**: Glory kill (when prompted near staggered enemies)
- **E/Q** or **Mouse Wheel**: Cycle through weapons
- **Esc**: Pause game
- **R**: Restart (when game over)

## Project Structure

- `src/player/` - Player character code and assets
- `src/weapons/` - Weapon system and individual weapons
- `src/enemies/` - Enemy AI and behavior
- `src/levels/` - Level design and layout
- `src/ui/` - HUD and menu interfaces
- `assets/` - Sprites, sounds, and music

## Current Development Status

This project is currently in active development. The following features are implemented:

- [x] Basic player movement and jumping
- [x] Weapon system framework
- [x] Enemy AI base class
- [x] Glory kill mechanics
- [x] Game state management
- [x] HUD display
- [ ] Complete level designs
- [ ] All weapon implementations
- [ ] Full enemy roster
- [ ] Boss battles
- [ ] Sound effects and music

## Contributing

Contributions are welcome! If you'd like to contribute:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Id Software for the original Doom
- Godot Engine for making game development accessible
- The Doom modding community for inspiration
