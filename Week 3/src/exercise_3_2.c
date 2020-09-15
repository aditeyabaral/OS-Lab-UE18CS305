#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Hello, %s!\n", argv[0]);
    printf("Leaving Child Process...\n\n");
    return 0;
}