#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void childProcess(int n);

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    pid_t pid = fork();
    if (!pid)
        childProcess(n);
    else
        wait(NULL);
    return 0;
}

void childProcess(int n)
{
    char buffer[100];
    if (n == 1)
    {
        printf("0\n");
        write(1, buffer, strlen(buffer));
    }
    else if (n == 2)
    {
        printf("0 1\n");
        write(1, buffer, strlen(buffer));
    }
    else if (n > 1)
    {
        int a = 0, b = 1, c = 0;
        printf("%d %d ", a, b);
        write(1, buffer, strlen(buffer));
        for (int i = 3; i <= n; i++)
        {
            c = a + b;
            printf("%d ", c);
            write(1, buffer, strlen(buffer));
            a = b;
            b = c;
        }
        printf("\n");
        write(1, buffer, strlen(buffer));
    }
    else
        ;
}