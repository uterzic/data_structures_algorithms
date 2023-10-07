#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int items[5];
    int count;
    int front;
    int rear;
} Queue;

Queue *makeQueue()
{
    Queue *newQueue = malloc(sizeof(Queue));
    newQueue->count = 0;
    newQueue->front = 0;
    newQueue->rear = 0;

    return newQueue;
}

void enqueue(Queue *queue, int item)
{
    if (queue->count == 5)
    {
        printf("Queue is full. Can't add more items.\n");
        return;
    }

    queue->items[queue->rear] = item;
    queue->rear = (queue->rear + 1) % 5;
    queue->count++;
}

int dequeue(Queue *queue)
{
    if (queue->count == 0)
    {
        printf("Queue is empty.");
        return -1;
    }

    int item = queue->items[queue->front];
    queue->items[queue->front] = 0;
    queue->front = (queue->front + 1) % 5;
    queue->count--;

    return item;
}

void printQueue(Queue *queue)
{
    if (queue->count == 0)
    {
        printf("Queue is empty.");
        return;
    }

    int i = queue->front;
    int count = 0;

    printf("Queue items:");
    while(count < queue->count)
    {
        printf(" %d", queue->items[i]);
        i = (i + 1) % 5;
        count++;
    }

    printf("\n");
}

int main()
{
    Queue *queue = makeQueue();

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);
    dequeue(queue);
    enqueue(queue, 60);
    enqueue(queue, 70);


    printQueue(queue);
}