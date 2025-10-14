#include <ncurses.h>
#include <locale.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

/* Map subpixel coordinates to braille dot bits
   dot indices (bits):
    (0,0)->1  (1,0)->8
    (0,1)->2  (1,1)->16
    (0,2)->4  (1,2)->32
    (0,3)->64 (1,3)->128
*/
static const int dotbit[2][4] = {
    {1,2,4,64},   /* x=0 */
    {8,16,32,128} /* x=1 */
};

static void braille_char_utf8(int mask, char *out){
    int cp = 0x2800 + (mask & 0xFF);
    out[0] = 0xE0 | (cp >> 12);
    out[1] = 0x80 | ((cp >> 6) & 0x3F);
    out[2] = 0x80 | (cp & 0x3F);
    out[3] = 0;
}

int main(void){
    setlocale(LC_CTYPE, "");
    initscr(); noecho(); curs_set(0); timeout(0);
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    /* logical pixel grid: width = cols*2, height = rows*4 */
    float gx = cols*2.0f/2.0f, gy = rows*4.0f/2.0f;
    float vx = 0.8f, vy = 0.4f;
    float radius = ((cols*2) < (rows*4) ? (cols*2) : (rows*4)) * 0.18f; /* tune size */

    char buf[4];
    for(;;){
        clear();
        getmaxyx(stdscr, rows, cols);
        /* recompute if terminal resized */
        int cell_w = cols, cell_h = rows;
        float cenx = gx, ceny = gy;

        /* iterate braille cells */
        for(int by=0; by<cell_h; ++by){
            for(int bx=0; bx<cell_w; ++bx){
                int mask = 0;
                /* each cell covers pixels (bx*2 + sx, by*4 + sy) */
                for(int sx=0;sx<2;++sx) for(int sy=0;sy<4;++sy){
                    float px = bx*2 + sx + 0.5f;
                    float py = by*4 + sy + 0.5f;
                    float dx = px - cenx;
                    float dy = py - ceny;
                    if (dx*dx + dy*dy <= radius*radius) mask |= dotbit[sx][sy];
                }
                if(mask){
                    braille_char_utf8(mask, buf);
                    mvaddstr(by, bx, buf);
                }
            }
        }

        refresh();

        /* motion and bounce in logical pixels */
        gx += vx; gy += vy;
        if(gx - radius < 0 || gx + radius > cols*2) vx = -vx;
        if(gy - radius < 0 || gy + radius > rows*4) vy = -vy;

        int ch = getch();
        if(ch == 'q') break;
        usleep(20000);
    }

    endwin();
    return 0;
}