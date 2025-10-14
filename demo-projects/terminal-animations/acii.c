#include <ncurses.h>

int main() {
    initscr();
    printw("Solid characters test:\n\n");
    printw("ASCII solids: # @ O * = | _ +\n");
    printw("Blocks: █ ▓ ▒ ░ ■ ◼ ⬛\n");
    printw("Circles: ● ⬤ ◉ ○ ◯\n");
    printw("Lines: ─ │ ┌ ┐ └ ┘ ═ ║ ╔ ╗ ╚ ╝\n");
    printw("Misc: ♦ ◆ ✶ ✸ ✹ ✦ ✧ ⣿ ⠿\n");
    refresh();
    getch();
    endwin();
    return 0;
}
