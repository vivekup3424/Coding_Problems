import os
import time
import keyboard
import random


class Fighter:
    def __init__(self, name, x_pos, facing_right=True):
        self.name = name
        self.x_pos = x_pos
        self.y_pos = 0  # Ground level
        self.health = 100
        self.facing_right = facing_right
        self.is_blocking = False
        self.is_jumping = False
        self.jump_height = 0
        self.is_punching = False
        self.is_kicking = False

        # Fighter states
        self.STANDING = ["  O  ", " /|\\ ", " / \\ "]

        self.BLOCKING = ["  O  ", " ||| ", " / \\ "]

        self.PUNCHING_RIGHT = ["  O  ", " |--> ", " / \\ "]

        self.PUNCHING_LEFT = ["  O  ", " <-| ", " / \\ "]

        self.KICKING_RIGHT = ["  O  ", " /|\\  ", " /--> "]

        self.KICKING_LEFT = ["  O  ", " /|\\ ", " <-\\ "]

        self.JUMPING = ["\\O/ ", " |  ", "/ \\ "]

    def get_current_sprite(self):
        if self.is_jumping:
            sprite = self.JUMPING
        elif self.is_blocking:
            sprite = self.BLOCKING
        elif self.is_punching:
            sprite = self.PUNCHING_RIGHT if self.facing_right else self.PUNCHING_LEFT
        elif self.is_kicking:
            sprite = self.KICKING_RIGHT if self.facing_right else self.KICKING_LEFT
        else:
            sprite = self.STANDING

        return sprite if self.facing_right else [line[::-1] for line in sprite]


class Game:
    def __init__(self):
        self.SCREEN_WIDTH = 80
        self.SCREEN_HEIGHT = 24
        self.GROUND_LEVEL = 20

        self.player1 = Fighter("Player 1", 20, True)
        self.player2 = Fighter("Player 2", 60, False)

        self.frame = 0
        self.game_over = False

    def clear_screen(self):
        os.system("cls" if os.name == "nt" else "clear")

    def check_collision(self):
        p1_sprite = self.player1.get_current_sprite()
        p2_sprite = self.player2.get_current_sprite()

        p1_width = len(p1_sprite[0])
        p2_width = len(p2_sprite[0])

        if abs(self.player1.x_pos - self.player2.x_pos) < (p1_width + p2_width) // 2:
            if self.player1.is_punching and not self.player2.is_blocking:
                self.player2.health -= 10
            if self.player2.is_punching and not self.player1.is_blocking:
                self.player1.health -= 10
            if self.player1.is_kicking and not self.player2.is_blocking:
                self.player2.health -= 15
            if self.player2.is_kicking and not self.player1.is_blocking:
                self.player1.health -= 15

    def draw_health_bars(self):
        p1_health = (
            "P1 Health: ["
            + "=" * (self.player1.health // 5)
            + " " * (20 - self.player1.health // 5)
            + "]"
        )
        p2_health = (
            "P2 Health: ["
            + "=" * (self.player2.health // 5)
            + " " * (20 - self.player2.health // 5)
            + "]"
        )
        print(
            p1_health
            + " " * (self.SCREEN_WIDTH - len(p1_health) - len(p2_health))
            + p2_health
        )

    def draw_frame(self):
        self.clear_screen()

        # Create empty screen
        screen = [
            [" " for _ in range(self.SCREEN_WIDTH)] for _ in range(self.SCREEN_HEIGHT)
        ]

        # Draw ground
        for x in range(self.SCREEN_WIDTH):
            screen[self.GROUND_LEVEL] = ["_" * self.SCREEN_WIDTH]

        # Draw fighters
        for fighter in [self.player1, self.player2]:
            sprite = fighter.get_current_sprite()
            y_offset = fighter.jump_height if fighter.is_jumping else 0
            for i, line in enumerate(sprite):
                y = self.GROUND_LEVEL - len(sprite) + i - y_offset
                for j, char in enumerate(line):
                    x = fighter.x_pos + j
                    if 0 <= x < self.SCREEN_WIDTH and 0 <= y < self.SCREEN_HEIGHT:
                        screen[y][x] = char

        # Print screen
        self.draw_health_bars()
        print("\n".join("".join(row) for row in screen))

        # Print controls
        print("\nPlayer 1: WASD + F(punch) G(kick) H(block)")
        print("Player 2: Arrow keys + K(punch) L(kick) ;(block)")
        print("Press ESC to quit")

    def handle_input(self):
        # Player 1 controls
        if keyboard.is_pressed("a") and self.player1.x_pos > 0:
            self.player1.x_pos -= 1
            self.player1.facing_right = False
        if keyboard.is_pressed("d") and self.player1.x_pos < self.SCREEN_WIDTH - 5:
            self.player1.x_pos += 1
            self.player1.facing_right = True
        if keyboard.is_pressed("w") and not self.player1.is_jumping:
            self.player1.is_jumping = True
        if keyboard.is_pressed("f"):
            self.player1.is_punching = True
        if keyboard.is_pressed("g"):
            self.player1.is_kicking = True
        if keyboard.is_pressed("h"):
            self.player1.is_blocking = True

        # Player 2 controls
        if keyboard.is_pressed("left") and self.player2.x_pos > 0:
            self.player2.x_pos -= 1
            self.player2.facing_right = False
        if keyboard.is_pressed("right") and self.player2.x_pos < self.SCREEN_WIDTH - 5:
            self.player2.x_pos += 1
            self.player2.facing_right = True
        if keyboard.is_pressed("up") and not self.player2.is_jumping:
            self.player2.is_jumping = True
        if keyboard.is_pressed("k"):
            self.player2.is_punching = True
        if keyboard.is_pressed("l"):
            self.player2.is_kicking = True
        if keyboard.is_pressed(";"):
            self.player2.is_blocking = True

        # Quit game
        if keyboard.is_pressed("esc"):
            self.game_over = True

    def update_game_state(self):
        # Update jumps
        for fighter in [self.player1, self.player2]:
            if fighter.is_jumping:
                if fighter.jump_height < 5:  # Rising
                    fighter.jump_height += 1
                else:  # Falling
                    fighter.jump_height -= 1
                    if fighter.jump_height == 0:
                        fighter.is_jumping = False

        # Reset attack states
        self.player1.is_punching = False
        self.player1.is_kicking = False
        self.player1.is_blocking = False
        self.player2.is_punching = False
        self.player2.is_kicking = False
        self.player2.is_blocking = False

        # Check win condition
        if self.player1.health <= 0:
            self.game_over = True
            print("\nPlayer 2 wins!")
        elif self.player2.health <= 0:
            self.game_over = True
            print("\nPlayer 1 wins!")

    def run(self):
        while not self.game_over:
            self.handle_input()
            self.update_game_state()
            self.check_collision()
            self.draw_frame()
            self.frame += 1
            time.sleep(0.05)


if __name__ == "__main__":
    game = Game()
    game.run()
