#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int items[5];
    int front;
    int rear;
    int count;
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
    queue->items[queue->rear++] = item;
    queue->count++;
}

int dequeue(Queue *queue)
{
    queue->count--;
    return queue->items[queue->front++];
}

void printQueue(Queue *queue)
{
    printf("In queue:");
    for (int i = queue->front; i < queue->rear; i++)
    {
        printf(" %d", queue->items[i]);
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
    dequeue(queue); 
    dequeue(queue);

    printQueue(queue);
}