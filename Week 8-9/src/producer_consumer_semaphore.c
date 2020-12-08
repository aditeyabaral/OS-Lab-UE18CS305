#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 50

int front = 0, rear = 0;
int *buffer;

sem_t mutex;
sem_t empty;
sem_t full;

void *producer();
void *consumer();

int main()
{
    buffer = (int *)malloc(sizeof(int) * BUF_SIZE);
    pthread_t thread1, thread2;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_create(&thread1, NULL, producer, NULL);
    sleep(1);

    pthread_create(&thread2, NULL, consumer, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    free(buffer);
    return 0;
}

void *consumer()
{
    while (true)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        int consumed = buffer[rear];
        printf("Consumed: %d\n", consumed);
        sleep(1);

        rear = (rear + 1) % BUF_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
    }
}

void *producer()
{
    int item = 0;
    while (true)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        item++;
        printf("Produced: %d\n", item);
        buffer[front] = item;

        sem_post(&mutex);
        sem_post(&full);
        front = (front + 1) % BUF_SIZE;
    }
}