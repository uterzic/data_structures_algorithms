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
    
    if (head == NULL) head = tail = newNode;
    else {
        newNode->next = head;
        head = newNode;
    }

    length++;
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
    int i = 0;

    while (i != index) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    prev->next = curr->next;
    free(curr);

    length--;
}

void deleteByValue(int value)
{
    Node* curr = head;
    Node* prev = NULL;

    while (curr->data != value) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    free(curr);

    length--;
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

int main()
{
    addLast(10);
    addLast(20);
    addLast(30);
    deleteAtIndex(1);
    addFirst(40);
    addLast(50);
    deleteByValue(30);
    addFirst(25);

    printList(head);
}