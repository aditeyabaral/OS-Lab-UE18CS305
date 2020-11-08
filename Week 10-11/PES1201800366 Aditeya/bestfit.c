#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int partition_id;
    int size;
    int total_cap;
    int is_alloc;
    char pid;
}partition;

typedef struct
{
    char pid;
    int mem;
    int partition_no;
}process;

void sort(partition* memory, int num_partitions)
{
    partition temp;
    for(int i=0; i<num_partitions; ++i)
    {
        for(int j=0; j<num_partitions-i-1; ++j)
        {
            if(memory[j].size > memory[j+1].size)
            {
                temp = memory[j];
                memory[j] = memory[j+1];
                memory[j+1] = temp;
            }
        }
    }
}

void sort_id(partition* memory, int num_partitions)
{
    partition temp;
    for(int i=0; i<num_partitions; ++i)
    {
        for(int j=0; j<num_partitions-i-1; ++j)
        {
            if(memory[j].partition_id > memory[j+1].partition_id)
            {
                temp = memory[j];
                memory[j] = memory[j+1];
                memory[j+1] = temp;
            }
        }
    }
}

void print_partition_data(partition* memory, int num_partitions)
{
    sort_id(memory, num_partitions);
    printf("Partition Number   Partition Size   Partition Status   Fragment Size\n"); 
    printf("--------------------------------------------------------------------\n");
    for(int i=0; i<num_partitions; ++i)
    {
        printf("%-19d", memory[i].partition_id);
        printf("%-17d", memory[i].total_cap);
        if(memory[i].is_alloc == 1)
        {
            printf("%-19s", "Allocated");
        }
        else
            printf("%-19s", "Free"); 
        printf("%-13d", memory[i].size);
        printf("\n");
    }
}

void print_process_data(process* p, int num_processes)
{
    printf("Process ID   Partition Allocated\n");
    printf("--------------------------------\n");
    for(int i=0; i<num_processes; ++i)
    {
        printf("%-13c", p[i].pid);
        if(p[i].partition_no != -1)
            printf("%d", p[i].partition_no);
        else
            printf("Not Allocated");
        printf("\n");
    }
}

void best_fit_alloc(partition* memory, int num_partitions, process* p, int num_processes)
{
    int i, j;
    for(i=0; i<num_processes; ++i)
    {
        for(j=0; j<num_partitions; ++j)
        {
            if(memory[j].size >= p[i].mem)
                break;
        } 
        if(j != num_partitions)    //Suitable partition was found
        {
            p[i].partition_no = memory[j].partition_id;
            memory[j].size -= p[i].mem;
            memory[j].is_alloc = 1;
            memory[j].pid = p[i].pid;
            sort(memory, num_partitions);
        }
        else                       //No suitable partition found, process not allocated
        {
            p[i].partition_no = -1;
        }
    }
}

int main()
{
    int num_processes, num_partitions;

    printf("Enter number of partitions in memory: ");
    scanf("%d", &num_partitions);
    partition memory[num_partitions];
    for(int i=0; i<num_partitions; ++i)
    {
        memory[i].partition_id = i;
        printf("Enter size of partition %d: ", i);
        scanf("%d", &(memory[i].size));
        memory[i].total_cap = memory[i].size;
        memory[i].is_alloc = 0;
    }
    sort(memory, num_partitions);

    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    process p[num_processes];

    for(int i=0; i<num_processes; ++i)
    {
        printf("Enter name of process: ");
        scanf(" %c", &(p[i].pid));
        printf("Enter size of process %c: ", p[i].pid);
        scanf("%d", &(p[i].mem));
        p[i].partition_no = -1;
    }
    best_fit_alloc(memory, num_partitions, p, num_processes);
    print_partition_data(memory, num_partitions);
    printf("\n\n");
    print_process_data(p, num_processes);

    return 0;
}