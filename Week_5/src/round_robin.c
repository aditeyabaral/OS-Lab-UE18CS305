#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void getBurstTime(int *, int *, int);
float getAverageWaitTime(int *, int *, int, int);
float getAverageTurnaroundTime(int *, int *, int *, int);
void display(int *, int *, int *, int *, int);

int main()
{
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    printf("\n");

    int *process = (int *)malloc(sizeof(int) * n);
    int *burst_times = (int *)malloc(sizeof(int) * n);
    int *wait_times = (int *)malloc(sizeof(int) * n);
    int *turnaround_times = (int *)malloc(sizeof(int) * n);

    getBurstTime(burst_times, process, n);
    float avg_wait_time = getAverageWaitTime(wait_times, burst_times, n, quantum);
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

void getBurstTime(int *burst_times, int *process, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_times[i]);
        process[i] = i + 1;
    }
}

float getAverageWaitTime(int *wait_times, int *burst_times, int n, int quantum)
{
    int *remaining_times = (int *)malloc(sizeof(int) * n);
    int remaining_processes = n, time = 0, process_number = 0, flag = true;
    float total_wait_time = 0;
    ;

    for (int i = 0; i < n; i++)
        remaining_times[i] = burst_times[i];

    while (true)
    {
        flag = true;
        for (int i = 0; i < n; i++)
        {
            if (remaining_times[i] > 0)
            {
                flag = false;
                if (remaining_times[i] > quantum)
                {
                    time += quantum;
                    remaining_times[i] -= quantum;
                }
                else
                {
                    time += remaining_times[i];
                    wait_times[i] = time - burst_times[i];
                    remaining_times[i] = 0;
                }
            }
        }
        if (flag)
            break;
    }

    for (int i = 0; i < n; i++)
        total_wait_time += wait_times[i];

    return total_wait_time / n;
}

float getAverageTurnaroundTime(int *turnaround_times, int *wait_times, int *burst_times, int n)
{
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        turnaround_times[i] = burst_times[i] + wait_times[i];
        total_turnaround_time += turnaround_times[i];
    }
    return total_turnaround_time / n;
}

void display(int *process, int *burst_times, int *wait_times, int *turnaround_times, int n)
{
    printf("\nJob\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t\t%d\t\t%d\n", process[i], burst_times[i], wait_times[i], turnaround_times[i]);
    printf("\n");
}