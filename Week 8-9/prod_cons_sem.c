#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define BUF_SIZE 20

int front = 0, rear=0;
int buffer[BUF_SIZE];

sem_t mutex;
sem_t empty;
sem_t full;

void* consumer()
{
    while(1)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        int consumed = buffer[rear];
        printf("Consumed item %d\n", consumed);
        sleep(1);
        rear = (rear+1)%BUF_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
    }
}

void* producer()
{
    int item = 0;
    while(1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        item += 1; //Producing an item
        printf("Producing item %d\n", item);
        buffer[front] = item;

        sem_post(&mutex);
        sem_post(&full);
        front = (front+1)%BUF_SIZE;
    }
}

int main()
{
    memset(buffer, 0, BUF_SIZE*sizeof(int));
    pthread_t thread1, thread2;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_create(&thread1, NULL, producer, NULL);
    sleep(1);
    pthread_create(&thread2, NULL, consumer, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}