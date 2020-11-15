#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct partition
{
    int partition_id;
    int size;
    int total_cap;
    int is_allocated;
    char process_id;
} PARTITION;

typedef struct process
{
    char process_id;
    int memory;
    int partition_number;
} PROCESS;

void sort(PARTITION *, int, char *);
void displayPartitionData(PARTITION *memory, PROCESS *p, int num_partitions, int num_processes);
void displayProcessData(PROCESS *, int);
void bestFitAllocation(PARTITION *, int, PROCESS *, int);

int main()
{
    int num_processes, num_partitions;

    printf("Enter number of partitions in memory: ");
    scanf("%d", &num_partitions);

    PARTITION memory[num_partitions];
    for (int i = 0; i < num_partitions; ++i)
    {
        memory[i].partition_id = i;
        printf("Enter size of PARTITION %d: ", i + 1);
        scanf("%d", &(memory[i].size));
        memory[i].total_cap = memory[i].size;
        memory[i].is_allocated = 0;
    }

    sort(memory, num_partitions, "size");

    printf("\nEnter number of processes: ");
    scanf("%d", &num_processes);

    PROCESS proc[num_processes];

    for (int i = 0; i < num_processes; ++i)
    {
        printf("Enter name of process: ");
        scanf(" %c", &(proc[i].process_id));
        printf("Enter size of process %c: ", proc[i].process_id);
        scanf("%d", &(proc[i].memory));
        proc[i].partition_number = -1;
        printf("\n");
    }
    printf("\n");

    bestFitAllocation(memory, num_partitions, proc, num_processes);
    displayPartitionData(memory, proc, num_partitions, num_processes);
    //displayProcessData(proc, num_processes);
    return 0;
}

void sort(PARTITION *memory, int num_partitions, char *mode)
{
    PARTITION temp;
    int cmp1, cmp2;

    for (int i = 0; i < num_partitions; i++)
    {
        for (int j = 0; j < num_partitions - i - 1; j++)
        {

            if (!strcmp(mode, "ID"))
            {
                cmp1 = memory[j].partition_id;
                cmp2 = memory[j + 1].partition_id;
            }
            else if (!strcmp(mode, "size"))
            {
                cmp1 = memory[j].size;
                cmp2 = memory[j + 1].size;
            }
            else
                ;

            if (cmp1 > cmp2)
            {
                temp = memory[j];
                memory[j] = memory[j + 1];
                memory[j + 1] = temp;
            }
        }
    }
}

void displayPartitionData(PARTITION *memory, PROCESS *p, int num_partitions, int num_processes)
{
    sort(memory, num_partitions, "ID");
    printf("Partition Number\t\tPartition Size\t\tPartition Status\t\tFragment Size\n");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < num_partitions; ++i)
    {
        printf("%-19d\t\t", memory[i].partition_id);
        printf("%-17d\t\t", memory[i].total_cap);
        if (memory[i].is_allocated == true)
        {
            printf("%s (%c)\t\t", "Allocated", memory[i].process_id);
        }
        else
            printf("%-19s\t\t", "Free");
        printf("%-13d\t\t", memory[i].size);
        printf("\n");
    }
}

void displayProcessData(PROCESS *p, int num_processes)
{
    printf("\nProcess ID\t\tPartition Allocated\n");
    printf("--------------------------------\n");
    for (int i = 0; i < num_processes; ++i)
    {
        printf("%-13c\t\t", p[i].process_id);
        if (p[i].partition_number != -1)
            printf("%d", p[i].partition_number);
        else
            printf("Not Allocated");
        printf("\n");
    }
}

void bestFitAllocation(PARTITION *memory, int num_partitions, PROCESS *p, int num_processes)
{
    int i, j;
    for (i = 0; i < num_processes; ++i)
    {
        for (j = 0; j < num_partitions; ++j)
        {
            if (memory[j].size >= p[i].memory)
                break;
        }

        if (j != num_partitions)
        {
            p[i].partition_number = memory[j].partition_id;
            memory[j].size -= p[i].memory;
            memory[j].is_allocated = 1;
            memory[j].process_id = p[i].process_id;
            sort(memory, num_partitions, "size");
        }
        else
        {
            p[i].partition_number = -1;
        }
    }
}