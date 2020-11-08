#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int page_number;
    struct node* next;
    struct node* prev;
}Node;

typedef struct list
{
    Node* front;
    Node* rear;
    int num_nodes;
}List;

int num_frames;    //Number of frames in physical memory

List* create_list()
{
    List* q = (List*)malloc(sizeof(List));
    q->front = q->rear = NULL;
    q->num_nodes = 0;
    return q;
}

Node* create_node(int page)
{
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->page_number = page;
    newnode->next = newnode->prev = NULL;
    return newnode;
}

void print_memory(List* q)
{
    Node* temp = q->front;
    int ctr = 0;
    while(temp != NULL)
    {
        printf("%-11d", temp->page_number);
        temp = temp->next;
        ctr +=1;
    }
    for(int i=ctr; i<num_frames; ++i)
        printf("%-11s","X");
}

int insert(List* q, int page_num)
{
    Node* newnode = create_node(page_num);
    if(q->front==NULL)  //Empty list
    {
        q->front = newnode;
        q->rear = newnode;
        q->num_nodes += 1;
        return -1;     //Page Fault
    }
    else
    {
        int flag = 0;
        Node* temp = q->front;
        while(temp != NULL)             //Check if page is in the memory already
        {
            if(temp->page_number == page_num)   //delete that node
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        } 
        if(flag)         //Page was found in memory
        {
            if(temp->page_number == q->front->page_number)  //Page queried was at the beginning of the list, do nothing
                //printf("FOUND AT FRONT!\n");
                ;
            else if(temp->next != NULL)       //page queried is in middle of list, delete it and insert again at the front
            {
                //printf("FOUND AT MIDDLE!\n");
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                free(temp);
                newnode->next = q->front;
                q->front->prev = newnode;
                q->front = newnode;
            }
            else                             //Page queried is at the rear of the list
            {
                //printf("FOUND AT REAR!\n");
                q->rear = temp->prev;
                temp->prev->next = NULL;
                free(temp);
                newnode->next = q->front;
                q->front->prev = newnode;
                q->front = newnode;
            }
            return 1;
        }
        else            //Page was not found in memory
        {
            //Need to insert new page
            if(q->num_nodes < num_frames)  //Memory is not full yet, insert page at front of queue
            {
                newnode->next = q->front;
                q->front->prev = newnode;
                q->front = newnode;
                q->num_nodes += 1;
            }
            else                            //Memory is full, need to perform LRU replacement
            {
                Node* temp = q->rear;       //Remove LRU page from the end, insert new page at the front
                q->rear = temp->prev;
                temp->prev->next = NULL;
                free(temp);
                newnode->next = q->front;
                q->front->prev = newnode;
                q->front = newnode;
            }
            return -1;
        }
    }
}

int main()
{
    int pf_count = 0, refs;
    printf("Enter length of reference string: ");
    scanf("%d", &refs);
    int ref_string[refs];
    printf("Enter reference string: ");
    for(int i=0; i<refs; ++i)
    {
        scanf("%d", &ref_string[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    List* q = create_list();

    for(int i=0; i<num_frames; ++i)
    {
        printf("Frame %d   ", i+1);
    }
    printf("\n-------------------------------------------\n");
    for(int i=0; i<refs; ++i)
    {
        int key = insert(q, ref_string[i]);
        print_memory(q);
        if(key == -1)
        {
            pf_count +=1;
            printf("Page fault no. : %d", pf_count);
        }
        printf("\n");
    }
    printf("Number of page faults: %d\n", pf_count);

    Node* temp = q->front;
    Node* temp1 = q->front;
    for(int i=0; i<q->num_nodes; ++i)
    {
        temp1 = temp->next;
        free(temp);
        temp = temp1;
    }
    free(q);
    return 0;
}