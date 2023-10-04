#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    struct node *prev;
    struct node *next;
    int data;
} Node;

Node *head = NULL;
Node *tail = NULL;
int length = 0;

Node *makeNode(int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL; 

    return newNode;
}

void addFirst(int value) 
{
    Node *newNode = makeNode(value);

    if (head == NULL) 
    {
        head = tail = newNode;
        newNode->next = head;
    } else {
        newNode->next = head;
        head = newNode;
        tail->next = head;
    }

    length++;
}

void addLast(int value)
{
    Node *newNode = makeNode(value);

    if (head == NULL) 
    {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    tail->next = head;

    length++;
}

void deleteByValue(int value)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    Node *current = head;
    Node *prev = NULL;

    while (current->data != value)
    {
        if (current->next == head)
        {
            printf("Value %d not found in the list.\n", value);
            return;
        }
        prev = current;
        current = current->next;
    }

    if (current == head)
    {
        // Deleting the head node
        if (current->next == head)
        {
            // If there is only one node in the list
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = current->next;
            tail->next = head;
        }
    }
    else if (current == tail)
    {
        // Deleting the tail node
        prev->next = head;
        tail = prev;
    }
    else
    {
        // Deleting a node in the middle
        prev->next = current->next;
    }

    free(current);
    length--;
}

void deleteByIndex(int index)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    if (index < 0 || index >= length)
    {
        printf("Invalid index.\n");
        return;
    }

    Node *temp = head;

    if (index == 0)
    {
        if (head->next == head)
        {
            head = NULL;
            tail = NULL;
        } 
        else
        {
            head = head->next;
            tail->next = head;
        }
    } 
    else
    {
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        if (temp == tail)
        {
            tail = temp->prev;
        }
    }

    free(temp);
    length--;
}

void searchValue(int value)
{
    Node *temp = head;

    for (int i = 0; i < length; i++)
    {
        if (temp->data == value)
        {
            printf("%d found in list.\n", value);
            return;
        }

        temp = temp->next;
    }

    printf("%d not found in list.\n", value);
}

void indexOf(int value)
{
    Node *temp = head;

    for (int i = 0; i < length; i++)
    {
        if (temp->data == value)
        {
            printf("Index of %d is: %d\n", value, i);
            return;
        }
        
        temp = temp->next;
    }

    printf("%d not found in list.\n", value);
}

void printList() 
{
    Node *temp = head;

    do 
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    } while(temp != head);

    printf("Length of list: %d\n", length);
}

void printInfinite()
{
    Node *temp = head;

    while (1)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main()
{
    addLast(10);
    addLast(20);
    addLast(30);

    deleteByIndex(1);

    printList();

    searchValue(10);
    indexOf(30);
}