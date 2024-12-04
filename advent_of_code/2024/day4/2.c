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

    for (int row = 1; row <= SIZE; row++) {
        for (int col = 1; col <= SIZE; col++) {
            chars[row-1][col-1] = content[(row-1) * SIZE + (col-1)];
        }
    }

    int count = 0;
    for (int row = 1; row < SIZE-2; row++) {
        for (int col = 1; col < SIZE-2; col++) {
            for (int h = -1; h <= 1; h+=2) {
                for (int v = -1; v <= 1; v+=2) {
                    bool cond1 = chars[row][col] == 'A';
                    bool cond2 =
                        chars[row + h*-1][col + h*-1] == 'M' &&
                        chars[row + h* 1][col + h* 1] == 'S';
                    bool cond3 =
                        chars[row + v*-1][col + v* 1] == 'M' &&
                        chars[row + v* 1][col + v*-1] == 'S';
                    if (cond1 && cond2 && cond3) count++;
                }
            }
        }
    }
    printf("count: %i\n", count);
}


