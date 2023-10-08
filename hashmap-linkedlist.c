#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    listSize = 5,
};

typedef struct entry
{
    int key;
    char value[10];
} Entry;

typedef struct node
{
    Entry *entry;
    struct node *next;
} Node;

typedef struct linkedList
{
    Node *head;
    Node *tail;
    int length;
} LinkedList;

Entry *makeEntry(int key, const char value[])
{
    Entry *newEntry = malloc(sizeof(Entry));
    newEntry->key = key;
    strncpy(newEntry->value, value, sizeof(newEntry->value));

    return newEntry;
}

Node *makeNode(int key, char value[])
{
    Node* newNode = malloc(sizeof(Node));
    newNode->entry = makeEntry(key, value);
    newNode->next = NULL;

    return newNode;
}

int hash(int key)
{
    return key % listSize;
}

void addFirst(LinkedList *list, int key, char value[])
{
    Node *newNode = makeNode(key, value);

    if (list->head == NULL) list->head = list->tail = newNode;
    else {
        newNode->next = list->head;
        list->head = newNode;
    }

    list->length++;
}

void addLast(LinkedList *list, int key, char value[])
{
    if (list->head == NULL)
    {
        addFirst(list, key, value);
        return;
    }

    Node* newNode = makeNode(key, value);

    list->tail->next = newNode;
    list->tail = newNode;

    list->length++;
}

// Free the memory for a linked list
void freeList(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current->entry); // Free the Entry
        free(current);        // Free the Node
        current = next;
    }
    free(list); // Free the LinkedList structure
}

void printList(LinkedList *list[])
{
    for (int i = 0; i < listSize; i++)
    {
        LinkedList *bucket = list[i];
        if (bucket == NULL) {
            printf("List on index [%d] is empty\n", i);
            continue;
        }

        Node *curr = bucket->head;
        printf("List on index [%d] has:", i);
        while (curr != NULL)
        {
            printf(" (K: %d V: %s)", curr->entry->key, curr->entry->value);
            curr = curr->next;
        }
        printf("\n");
    }
}


void put(LinkedList *list[], int key, char value[]) {
    int index = hash(key);
    if (list[index] == NULL)
    {
        list[index] = malloc(sizeof(LinkedList));
        list[index]->head = NULL; // Initialize the linked list
        list[index]->tail = NULL;
        list[index]->length = 0;
    }

    LinkedList *bucket = list[index];

    // Check if the key already exists and update its value
    Node *current = bucket->head;
    while (current != NULL)
    {
        if (current->entry->key == key)
        {
            strncpy(current->entry->value, value, sizeof(current->entry->value));
            return;
        }
        current = current->next;
    }

    // If the key is not found, add it to the end of the linked list
    addLast(bucket, key, value);
}

char *get(LinkedList *list[], int key) {
    int index = hash(key);
    LinkedList *bucket = list[index];

    if (bucket != NULL) {
        Node *current = bucket->head;
        while (current != NULL) {
            if (current->entry->key == key) {
                return current->entry->value;
            }
            current = current->next;
        }
    }

    return NULL;
}

void deleteAtIndex(LinkedList *bucket, int index)
{
    Node* curr = bucket->head;
    Node* prev = NULL;
    int i = 0;

    // Traverse the list to find the node at the specified index
    while (i != index && curr != NULL) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    // Check if we found the node at the specified index
    if (i == index && curr != NULL) {
        if (prev != NULL) {
            prev->next = curr->next;
        } else {
            // If the node to be deleted is the head of the list
            bucket->head = curr->next;
        }

        if (curr == bucket->tail) {
            // If the node to be deleted is the tail of the list
            bucket->tail = prev;
        }

        // Free the memory for the node and its entry
        free(curr);
//        if (i == 0) {
//            // If we deleted the head, update the head pointer
//            free(bucket);
//            return;
//        }
        bucket->length--;
    }
}

void removeKey(LinkedList *list[], int key) {
    int index = hash(key);
    LinkedList *bucket = list[index];
    if (bucket == NULL)
        return;

    Node *current = bucket->head;
    Entry *entry;
    int i = 0;
    while (current != NULL)
    {
        entry = current->entry;
        if (entry->key == key) {
            deleteAtIndex(bucket, i);
            return;
        }
        current = current->next;
        i++;
    }
}

int main()
{
    LinkedList **list = calloc(listSize, sizeof(LinkedList*));

    // Initialize all elements to NULL
    for (int i = 0; i < listSize; i++) {
        list[i] = NULL;
    }

    put(list, 24, "Uros");
    put(list, 21, "Nina");
    put(list, 7, "Laza");
    put(list, 2, "Dudlica");

    printf("Value for key 21: %s\n", get(list, 21));
    removeKey(list, 2);
    removeKey(list, 7);

    printList(list);

    // Free the allocated memory when done
    for (int i = 0; i < listSize; i++) {
        if (list[i] != NULL) {
            freeList(list[i]);
        }
    }

    // Free the array itself
    free(list);

    return 0;
}
