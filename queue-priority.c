#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define ARR_SIZE 5

typedef struct priorityQueue
{
    int items[ARR_SIZE];
    int count;
} PriorityQueue;

PriorityQueue *makeQueue()
{
    PriorityQueue *newQueue = malloc(sizeof(PriorityQueue));
    newQueue->count = 0;

    return newQueue;
}

bool isFull(PriorityQueue *queue)
{
    return queue->count == ARR_SIZE;
}

bool isEmpty(PriorityQueue *queue)
{
    return queue->count == 0;
}

int shiftItemsToInsert(PriorityQueue *queue, int value, int array_size)
{
    int i;
    for (i = queue->count - 1; i >= 0; i--)
    {
        if (value < queue->items[i])
        {
            queue->items[i + 1] = queue->items[i];
        }
        else
        {
            break;
        }
    }

    return i + 1;
}

void enqueue(PriorityQueue *queue, int value)
{
    if(isFull(queue))
    {
        printf("Priority Queue is full. Can't insert %d.\n", value);
        return;
    }

    int indexForPlacement = shiftItemsToInsert(queue, value, ARR_SIZE);

    queue->items[indexForPlacement] = value;
    queue->count++;
}

void printPriorityQueue(PriorityQueue *queue)
{
    if(isEmpty(queue))
    {
        printf("Priority Queue is empty.");
        return;
    }

    printf("Items in Priority Queue:");
    for (int i = 0; i < queue->count; i++)
    {
        printf(" %d", queue->items[i]);
    }
    printf("\n");
}

int dequeue(PriorityQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("Priority Queue is empty.");
        return -1;
    }

    return queue->items[--queue->count];
}


int main()
{
    PriorityQueue *queue = makeQueue();
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);
    enqueue(queue, 60);

    printf("Removed item %d.\n", dequeue(queue));

    printPriorityQueue(queue);
    return 0;
}