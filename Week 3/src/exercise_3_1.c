#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void childProcess(char *name);
void parentProcess(char *name);

int main()
{
    char *name = (char *)malloc(sizeof(char) * 100);
    memset(name, 0, 100);
    printf("Enter name: ");
    scanf("%s", name);

    pid_t pid = fork();
    if (!pid)
        childProcess(name);
    else
    {
        wait(NULL);
        parentProcess(name);
    }
    free(name);
    return 0;
}

void childProcess(char *name)
{
    char *args[] = {name, NULL};
    execv("./greeting", args);
}

void parentProcess(char *name)
{
    char buffer[100];
    printf("Goodbye, %s\n", name);
    write(1, buffer, strlen(buffer));
}