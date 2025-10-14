#include <ncurses.h>
#include <unistd.h>

int main(void){
    initscr(); noecho(); curs_set(0); timeout(0);
    int r,c; getmaxyx(stdscr,r,c);
    float x=c/2.0f, y=r/2.0f, dx=0.6f, dy=0.3f;
    for(;;){
        clear();
        mvprintw((int)y+1, (int)x+1, "⬤⬤");
        mvprintw((int)y,(int)x,"⬤⬤⬤⬤");
        mvprintw((int)y-1,(int)x+1,"⬤⬤");
        refresh();
        x+=dx; y+=dy;
        if(x<1||x>c-2) dx=-dx;
        if(y<1||y>r-2) dy=-dy;
        if(getch()=='q') break;
        usleep(10000);
    }
    endwin();
    return 0;
}
