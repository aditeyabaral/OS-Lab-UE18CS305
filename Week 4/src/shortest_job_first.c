#include <stdio.h>
#include <stdlib.h>

void getBurstTime(int *, int *, int);
void sort(int *, int *, int);
float getAverageWaitTime(int *, int *, int);
float getAverageTurnaroundTime(int *, int *, int *, int);
void display(int *, int *, int *, int *, int);

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("\n");

    int *process = (int *)malloc(sizeof(int) * n);
    int *burst_times = (int *)malloc(sizeof(int) * n);
    int *wait_times = (int *)malloc(sizeof(int) * n);
    int *turnaround_times = (int *)malloc(sizeof(int) * n);

    getBurstTime(burst_times, process, n);
    sort(burst_times, process, n);
    float avg_wait_time = getAverageWaitTime(wait_times, burst_times, n);
    float avg_turnaround_time = getAverageTurnaroundTime(turnaround_times, wait_times, burst_times, n);

    display(process, burst_times, wait_times, turnaround_times, n);
    printf("Average Waiting Time: %f\n", avg_wait_time);
    printf("Average Turnaround Time: %f\n", avg_turnaround_time);

    free(process);
    free(burst_times);
    free(wait_times);
    free(turnaround_times);
    return 0;
}
void sort(int *times, int *process, int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (times[j] > times[j + 1])
            {
                temp = times[j];
                times[j] = times[j + 1];
                times[j + 1] = temp;

                temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

float getAverageWaitTime(int *wait_times, int *burst_times, int n)
{
    float avg_wait_time = 0;
    wait_times[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wait_times[i] = 0;
        for (int j = 0; j < i; j++)
            wait_times[i] += burst_times[j];
        avg_wait_time += wait_times[i];
    }
    return avg_wait_time / n;
}

float getAverageTurnaroundTime(int *turnaround_times, int *wait_times, int *burst_times, int n)
{
    float avg_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        turnaround_times[i] = burst_times[i] + wait_times[i];
        avg_turnaround_time += turnaround_times[i];
    }
    return avg_turnaround_time / n;
}

void getBurstTime(int *burst_times, int *process, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_times[i]);
        process[i] = i + 1;
    }
}

void display(int *process, int *burst_times, int *wait_times, int *turnaround_times, int n)
{
    printf("\nJob\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t\t%d\t\t%d\n", process[i], burst_times[i], wait_times[i], turnaround_times[i]);
    printf("\n");
}