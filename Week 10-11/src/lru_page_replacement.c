#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int page;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct list
{
    NODE *front;
    NODE *rear;
    int nodes;
} LIST;

int frames;
LIST *createList();
NODE *createNode(int);
void displayMemory(LIST *);
int insert(LIST *, int);

int main()
{
    int pf_count = 0, refs;
    printf("Enter length of reference string: ");
    scanf("%d", &refs);

    int *ref_string = (int *)malloc(sizeof(int) * refs);
    printf("Enter reference string: ");
    for (int i = 0; i < refs; ++i)
    {
        scanf("%d", &ref_string[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    LIST *l = createList();

    for (int i = 0; i < frames; ++i)
        printf("Frame %d\t\t", i + 1);
    printf("Page Fault");

    printf("\n------------------------------------------------------------------\n");
    for (int i = 0; i < refs; ++i)
    {
        int key = insert(l, ref_string[i]);
        displayMemory(l);
        if (key == -1)
        {
            pf_count += 1;
            printf("%d", pf_count);
        }
        printf("\n");
    }
    printf("Number of page faults: %d\n", pf_count);

    NODE *temp = l->front;
    NODE *temp1 = l->front;
    for (int i = 0; i < l->nodes; ++i)
    {
        temp1 = temp->next;
        free(temp);
        temp = temp1;
    }
    free(l);
    free(ref_string);
    return 0;
}

LIST *createList()
{
    LIST *l = (LIST *)malloc(sizeof(LIST));
    l->front = NULL;
    l->rear = NULL;
    l->nodes = 0;
    return l;
}

NODE *createNode(int page)
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    new_node->page = page;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void displayMemory(LIST *l)
{
    NODE *pres = l->front;
    int ctr = 0;
    while (pres != NULL)
    {
        printf("%-11d\t", pres->page);
        pres = pres->next;
        ctr += 1;
    }
    for (int i = ctr; i < frames; i++)
        printf("%-11s\t", "-");
}

int insert(LIST *l, int page)
{
    NODE *new_node = createNode(page);
    if (l->front == NULL)
    {
        l->front = new_node;
        l->rear = new_node;
        l->nodes += 1;
        return -1;
    }

    else
    {
        int flag = false;
        NODE *temp = l->front;
        while (temp != NULL)
        {
            if (temp->page == page)
            {
                flag = true;
                break;
            }
            temp = temp->next;
        }
        if (flag)
        {
            if (temp->page == l->front->page)
                ;
            else if (temp->next != NULL)
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                free(temp);
                new_node->next = l->front;
                l->front->prev = new_node;
                l->front = new_node;
            }
            else
            {
                l->rear = temp->prev;
                temp->prev->next = NULL;
                free(temp);
                new_node->next = l->front;
                l->front->prev = new_node;
                l->front = new_node;
            }
            return 1;
        }
        else
        {
            if (l->nodes < frames)
            {
                new_node->next = l->front;
                l->front->prev = new_node;
                l->front = new_node;
                l->nodes += 1;
            }
            else
            {
                NODE *temp = l->rear;
                l->rear = temp->prev;
                temp->prev->next = NULL;
                free(temp);
                new_node->next = l->front;
                l->front->prev = new_node;
                l->front = new_node;
            }
            return -1;
        }
    }
}