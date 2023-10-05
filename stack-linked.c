#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next;
    int item;
} Node;

Node *head = NULL;

Node *makeNode(int item)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->item = item;

    return newNode;
}

int isEmpty()
{   
    return head == NULL;
}

void push(int item)
{
    Node *newNode = makeNode(item);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    newNode->next = head;
    head = newNode;
}

void pop()
{
    if (isEmpty())
    {
        printf("Can't pop. Stack is empty.\n");
        return;
    }

    Node *temp = head;
    head = head->next;

    printf("Pop: %d\n", temp->item);
    free(temp);
}

void peek()
{   
    if (isEmpty())
    {
        printf("Can't peek. Stack is empty.\n");
    }
    printf("Peek: %d\n", head->item);
}


void printStack()
{
    if (isEmpty())
    {
        printf("Can't print. Stack is empty.\n");
        return;
    }
    
    printf("Stack items: ");
    Node *current = head;

    while (current != NULL)
    {
        printf("%d ", current->item);
        current = current->next;
    }

    printf("\n");
}

int main()
{
    push(10);
    printStack();
    peek();
    pop();
    printStack();
}
