#include "Header.h"
int main()
{
    int n;
    printf("Enter size of Array: ");
    scanf("%d", &n);

    int *a = (int*)calloc(n, sizeof(int));

    printf("Enter elements: ");
    for(int i = 0; i<n; i++)
        scanf("%d", &a[i]);

    printf("Input Array:\n");
    display_array(a, n);

    printf("Reversed Array:\n");
    reverse_array(a, n);

    free(a);
    return 0;
}