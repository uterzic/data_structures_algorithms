#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;
int length = 0;

Node *makeNode(int value)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

void addFirst(int value)
{
    Node *newNode = makeNode(value);
    newNode->next = head;

    head = newNode;

    if (tail == NULL)
    {
        tail = newNode;
    }

    length++;
}

void printList(Node* head)
{
    Node* curr = head;

    while (curr != NULL)
    {
        printf("%d\n", curr->data);
        curr = curr->next;
    }

    printf("Length: %d\n", length);
}

Node* findLast()
{
    Node* curr = head;

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

    Node* newNode = makeNode(value);

    tail->next = newNode;
    tail = newNode;

    length++;
}

void deleteAtIndex(int index)
{
    Node* curr = head;
    Node* prev = NULL;

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
    Node* curr = head;
    if (curr->data == value)
    {
        head = curr->next;

        free(curr);
        length--;

        return;
    }

    Node* prev = NULL;
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