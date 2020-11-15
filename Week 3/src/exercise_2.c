#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void childProcess(int *a, int n);
void parentProcess(int *a, int n);

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *a = (int *)malloc(sizeof(int) * n);
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid_t pid = fork();
    if (!pid)
        childProcess(a, n);
    else
    {
        wait(NULL);
        parentProcess(a, n);
    }
    free(a);
    return 0;
}

void childProcess(int *a, int n)
{
    char buffer[100];
    int temp[n];
    memset(temp, 0, n);
    temp[0] = a[0];
    for (int i = 1; i < n; i++)
        temp[i] = temp[i - 1] + a[i];
    printf("Partial Sum = %d\n", temp[n - 1]);
    write(1, buffer, strlen(buffer));
}

void parentProcess(int *a, int n)
{
    char buffer[100];
    int temp[n];
    memset(temp, 0, n);
    temp[0] = a[0];
    for (int i = 1; i < n; i++)
        temp[i] = temp[i - 1] * a[i];
    printf("Partial Product = %d\n", temp[n - 1]);
    write(1, buffer, strlen(buffer));
}