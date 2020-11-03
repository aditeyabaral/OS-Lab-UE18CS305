#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <wait.h>

void producer(FILE *);
void consumer(FILE *);

int main()
{
    int file_descriptor[2];
    if (pipe(file_descriptor) < 0)
        exit(1);

    FILE *pipe_read = fdopen(file_descriptor[0], "r");
    FILE *pipe_write = fdopen(file_descriptor[1], "w");

    pid_t producer_pid = fork();
    if (producer_pid == 0)
    {
        fclose(pipe_read);
        producer(pipe_write);
    }

    pid_t consumer_pid = fork();
    if (consumer_pid == 0)
    {
        fclose(pipe_write);
        consumer(pipe_read);
    }

    fclose(pipe_read);
    fclose(pipe_write);
    wait(NULL);
    wait(NULL);

    return 0;
}

void producer(FILE *pipe_write)
{
    int item = 0;
    for (int i = 0; i < 10; ++i)
    {
        item++;
        fprintf(pipe_write, "%d ", item);
        printf("Produced: %d\n", item);
    }
    fclose(pipe_write);
    exit(0);
}

void consumer(FILE *pipe_read)
{
    int consumed, n;
    while (true)
    {
        n = fscanf(pipe_read, "%d", &consumed);
        if (n == 1)
            printf("Consumed: %d\n", consumed);
        else
            break;
    }
    fclose(pipe_read);
    exit(0);
}