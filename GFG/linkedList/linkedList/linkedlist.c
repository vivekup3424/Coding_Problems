#include <stdio.h>
#include <stdlib.h>
struct list     //i am replacing 'node' by 'list' in structure, due to some issue
{
    int data;
    struct list *next;
};
struct LinkedList
{
    struct list *Head;
};

struct list *create_singly_linked_list()
{
    struct list *start = (struct list *)malloc(sizeof(struct list));
    printf("Size of start node = %lu",sizeof(struct list));
    printf("Size of start pointer = %lu",sizeof(start));
    struct list *ptr1 = (struct list *)malloc(sizeof(struct list));
    int i=0,data=-1;
    char c;
    printf("Enter the data of first node: ");
    scanf("%d",&data);
    ptr1->data = data;
    ptr1->next = NULL;
    start = ptr1;
    printf("Input 'n' to stop: ");
    scanf(" %c",&c);
    while (c!='n')
    {
        struct list *ptr2 = (struct list *)malloc(sizeof(struct list));
        printf("Enter the data of next node: ");
        scanf("%d",&data);
        ptr2->data = data;
        ptr1->next = ptr2;
        ptr1 = ptr2;
        printf("Input 'n' to stop: ");
        scanf(" %c",&c);

    }
    return start;
}
void print_singly_linked_list(struct list *start)
{
    int i = 1;
    struct list *current = start;
    if (start == NULL)
    {
        printf("Empty linked list");
    }
    else
    {
        printf("Elments of the list are: \n");
        while (current!=NULL)
        {
            printf("Node %d data = %d\n",i,current->data);
            i++;
            current = current->next;
        }
    }
}
void printList(struct list *n)
{
	while(n!=NULL)
	{
		printf("data = %d\n",n->data);
		n = n->next;
	}
}
void insert_singly_linked_list (struct list *start, int position, float element)
{
    struct list *ptr1 = (struct list *)malloc(sizeof(struct list));
    struct list *ptr2 = (struct list *)malloc(sizeof(struct list));
    struct list *ptr = (struct list *)malloc(sizeof(struct list));
    int i = 1;
    ptr->data = element;
    ptr->next = NULL;
    if (start==NULL)
    {
        if (position == 1)
        {
            start = ptr;
            return;    
        }
        else
        {
            printf("\nOut of bound.\nCan not insert element at %d",position);
            printf(" position as list is empty.\n");
            exit(1);
        }
    }
    ptr1 = start;
    ptr2 = start->next;
    
    while (i<position-1)
    {
        if (ptr1==NULL)
        {
            printf("\nOut of bound.\n");
            return;
        }
        
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        i++;
    }
    ptr1->next = ptr;
    ptr->next = ptr2;
}
float delete_singly_linked_list(struct list *start,int position)
{
    float deleted_num = -1.00;
    if (start==NULL)
    {
        printf("\nThe list is empty.\n");
        exit(1);
    }
    else if (start!=NULL && position==1)
    {
        struct list *ptr = (struct list *)(malloc(sizeof(struct list)));
        ptr = start;
        start = ptr->next;
        free(ptr);
    }
    else
    {
        int i=1;
        struct list *ptr1 = (struct list *)(malloc(sizeof(struct list)));
        struct list *ptr2 = (struct list *)(malloc(sizeof(struct list)));
        ptr1 = start;
        ptr2 = ptr1->next;
        while(i<position-1) //finding the predecessor
        {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;    
        }
        if (ptr2 == NULL)
        {
            printf("\nOut of bound position,\n");
            printf("there no element to be deleted at %d position.\n",position);
        }
        else
        {
            ptr1->next = ptr2->next;
            deleted_num = ptr2->data;
            free(ptr2);
        }
    }
    return deleted_num;
}
int search_singly_linked_list (struct list *start, float element)
{
    if (start==NULL)
    {
        printf("The list is empty.\n");
        return -1;
    }
    else
    {
        int counter=1; /*counter*/
        struct list *ptr1 = (struct list *)(malloc(sizeof(struct list)));
        ptr1 = start;
        while (ptr1!=NULL)
        {
            if (ptr1->data == element)
            {
                printf("\nThe position of element %0.2f is = %d\n",element,counter);
                return counter;
            }
            else
            {
                ptr1 = ptr1->next;
                counter++;
            }
        }
        printf("\nThe element %0.2f is not found in linked list.\n",element);
        return -1;
            
    }
    

}

/*traversal*/
void traverse_list(struct list *start)
{
	int i = 1;
	struct list *current;
	current = start;
	while(current!=NULL)
	{
		printf("\nNode %d data = %d",i,current->data);
		i++;
		current = current->next;
	}
}
/*Insertion*/
void insert_node(struct list *n)
{
    
}

struct list *list_search(struct list *head,int k) //returns pointer to the node for which data = k
{
    struct list *temp = (struct list *)malloc(sizeof(struct list));
    temp = head;
    while(temp!=NULL && temp->data != k)
    {
        temp = temp->next;
    }
    return temp;
}
int main()
{
    /*Initialize Node*/
    struct list *head = NULL;
    struct list *second = NULL;
    struct list *third = NULL;

    /*Allocate memory*/
    head = (struct list *)malloc(sizeof(struct list));
    second = (struct list *)malloc(sizeof(struct list));
    third = (struct list *)malloc(sizeof(struct list));

    /*Assign data values*/
    head->data = 1;
    second->data = 2;
    third->data = 3;

    /*Connect Nodes*/
    head->next = second;
    second->next = third;

    /*Form the list*/
    struct LinkedList *List;
    List->Head = head;
	
	printList(head);
	
}

