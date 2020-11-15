#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#define BUFFER_SIZE 100

void *producer();
void *consumer();

int front = 0, rear = 0;
int *buffer;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t empty = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t full = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    buffer = (int *)malloc(sizeof(int) * BUFFER_SIZE);
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    sleep(1);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    free(buffer);
    return 0;
}

void *producer()
{
    int item = 0;
    while(true)
    {
        pthread_mutex_lock(&empty);
        pthread_mutex_lock(&mutex);
        item += 1;
        printf("Job Initiated: %d\n", item);
        buffer[front] = item;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&full);
        front = (front + 1) % BUFFER_SIZE;
    }
}

void *consumer()
{
    while(true)
    {
        pthread_mutex_lock(&full);
        pthread_mutex_lock(&mutex);
        int consumed = buffer[rear];
        printf("Job Completed: %d\n", consumed);
        sleep(1);
        rear = (rear + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&empty);
    }
}