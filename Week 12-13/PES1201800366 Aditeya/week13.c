#include <stdio.h>
#include <stdlib.h>

float getSeekTime(int, int, int *);

int main()
{
    int max_range, q_size, initial_position, *q_positions;

    printf("Enter max range of disk: ");
    scanf("%d", &max_range);

    printf("Enter size of queue: ");
    scanf("%d", &q_size);
    q_positions = (int *)malloc(sizeof(int) * q_size);

    printf("\nEnter queue of disk positions to read:\n");
    for (int i = 0; i < q_size; i++)
        scanf("%d", &q_positions[i]);

    printf("\nEnter initial position: ");
    scanf("%d", &initial_position);
    printf("\n");

    float seek_time = getSeekTime(initial_position, q_size, q_positions);
    float avg_seek_time = seek_time / q_size;

    printf("\nTotal Seek Time = %f\n", seek_time);
    printf("Average Seek Time = %f\n", avg_seek_time);

    free(q_positions);
    return 0;
}

float getSeekTime(int initial_position, int q_size, int *q_positions)
{
    float seek = 0.0;
    for (int i = 0; i < q_size; i++)
    {
        printf(
            "Disk head moves from %d to %d with seek = %d\n",
            initial_position,
            q_positions[i],
            abs(initial_position - q_positions[i])
            );

        seek += abs(initial_position - q_positions[i]);
        initial_position = q_positions[i];
    }
    return seek;
}