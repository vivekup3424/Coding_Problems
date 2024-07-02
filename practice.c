#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    char *src = "hello";
    char *dst = (char *)malloc(strlen(src) + 1);
    strcpy(dst, src);
    int m = strlen(src);
    printf("m = %d\n", m);
    printf("src = %s,dst = %s\n", src, dst);
    free(dst);
    return 0;
}
