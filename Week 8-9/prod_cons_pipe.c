#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
void producer(FILE* pipe_write_end)
{
    int item = 0;
    for(int i=0; i<15; ++i)
    {
        item+=1;
        fprintf(pipe_write_end, "%d ", item);
        printf("Producer: Wrote %d\n", item);
    }
    fclose(pipe_write_end);
    exit(0);
}

void consumer(FILE* pipe_read_end)
{
    int next_consumed, n;
    while(1)
    {
        n = fscanf(pipe_read_end, "%d", &next_consumed);
        if(n==1)
            printf("Consumer: Consumed %d\n", next_consumed);
        else
            break;
    }
    fclose(pipe_read_end);
    exit(0);
}

int main()
{
    int fd[2]; //File descriptors for the pipe
    if(pipe(fd) < 0)
        exit(1); //Pipe creation unsuccessful
    FILE* pipe_read_end  = fdopen(fd[0], "r");
    FILE* pipe_write_end = fdopen(fd[1], "w");

    pid_t producer_pid = fork();  //Fork the producer process
    if(producer_pid == 0)
    {
        fclose(pipe_read_end);
        producer(pipe_write_end);
    }

    pid_t consumer_pid = fork(); //Fork the consumer process
    if(consumer_pid == 0)
    {
        fclose(pipe_write_end);
        consumer(pipe_read_end);
    }

    fclose(pipe_read_end);
    fclose(pipe_write_end);

    //Wait for both producer and consumer processes to terminate
    wait(NULL);  
    wait(NULL);

    return 0;
}