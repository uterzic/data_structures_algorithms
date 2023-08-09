#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;
int length = 0;

struct node* makeNode(int value)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;
}

void addFirst(int value)
{
    struct node* newNode = makeNode(value);
    newNode->next = head;

    head = newNode;

    if (tail == NULL)
    {
        tail = newNode;
    }

    length++;
}

void printList(struct node* head)
{
    struct node* curr = head;

    while (curr != NULL)
    {
        printf("%d\n", curr->data);
        curr = curr->next;
    }

    printf("Length: %d", length);
}

struct node* findLast()
{
    struct node* curr = head;

    while (curr->next != NULL)
    {
        curr = curr->next;
    }

    return curr;
}

void addLast(int value)
{
    if (head == NULL)
    {
        addFirst(value);
        return;
    }

    struct node* newNode = makeNode(value);

    tail->next = newNode;
    tail = newNode;

    length++;
}

void deleteAtIndex(int index)
{
    struct node* curr = head;
    struct node* prev = NULL;

    for (int i = 0; i != index; i++)
    {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    free(curr);

    length--;
}

void deleteByValue(int value)
{
    struct node* curr = head;
    if (curr->data == value)
    {
        head = curr->next;

        free(curr);
        length--;

        return;
    }

    struct node* prev = NULL;
    while (curr->data != value)
    {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    free(curr);

    length--;
}

int main()
{
    addFirst(10);
    addFirst(20);
    addFirst(30);
    addLast(40);
    
    printList(head);
}