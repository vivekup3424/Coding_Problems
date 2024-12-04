#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 141

char* read_entire_file(char* filename) {
    FILE* file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* str = malloc(fsize + 1);
    fread(str, fsize, 1, file);
    fclose(file);

    str[fsize] = 0;
    return str;
}

int main() {
    char *content = read_entire_file("./input");
    char chars[SIZE][SIZE];
    //frienfs dont belive me
    for (int row = 1; row <= SIZE; row++) {
        for (int col = 1; col <= SIZE; col++) {
            chars[row-1][col-1] = content[(row-1) * SIZE + (col-1)];
        }
    }

    int count = 0;
    for (int row = 0; row < SIZE-1; row++) {
        for (int col = 0; col < SIZE-1; col++) {
            for (int h = -1; h <= 1; h++) {
                for (int v = -1; v <= 1; v++) {
                    if (row + h*3 < 0 || row + h*3 > SIZE-1 || col + v*3 < 0 || col + v*3 > SIZE-1) continue;
                    bool cond =
                        chars[row + h*0][col + v*0] == 'X' &&
                        chars[row + h*1][col + v*1] == 'M' &&
                        chars[row + h*2][col + v*2] == 'A' &&
                        chars[row + h*3][col + v*3] == 'S';
                    if (cond) count++;
                }
            }
        }
    }
    printf("count: %i\n", count);

    return 0;
    // debug
    for (int row = 1; row < SIZE; row++) {
        for (int col = 1; col < SIZE; col++) {
            printf("%c", chars[row-1][col-1]);
        }
        printf("\n");
    }
}
