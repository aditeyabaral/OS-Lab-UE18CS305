#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#define BUFFER_SIZE 100

void *producer();
void *consumer();

int front = 0, rear = 0;
int item = 0;
int *buffer;

int main()
{
    buffer = (int *)malloc(sizeof(int) * BUFFER_SIZE);
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    free(buffer);
    return 0;
}

void *producer()
{
    while (true)
    {
        item += 1;
        printf("Job Initiated: %d\n", item);
        sleep(1);
        while (((front + 1) % BUFFER_SIZE) == rear)
            ;
        buffer[front] = item;
        front = (front + 1) % BUFFER_SIZE;
    }
}

void *consumer()
{
    while (true)
    {
        while (front == rear)
            ;
        int consumed = buffer[rear];
        printf("Job Completed: %d\n", consumed);
        sleep(1);
        rear = (rear + 1) % BUFFER_SIZE;
    }
}