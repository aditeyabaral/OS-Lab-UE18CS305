#include "Header.h"
void reverse_array(int *a, int n)
{
    int temp, start = 0, end = n - 1;
    while (start < end)
    {
        temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++;
        end--;
    }
    display_array(a, n);
}

void display_array(int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}