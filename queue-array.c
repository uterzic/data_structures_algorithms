#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int items[5];
    int front;
    int rear;
    int count;
} Queue;

int isEmpty(Queue*);

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

void peek(Queue *queue)
{
    printf("Peek: %d\n", queue->items[queue->front]);
}

void printQueue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("In queue:");
    for (int i = queue->front; i < queue->rear; i++)
    {
        printf(" %d", queue->items[i]);
    }
    printf("\n");
}

int isEmpty(Queue *queue)
{
    return queue->count == 0;
}

int main()
{
    Queue *queue = makeQueue();
    printQueue(queue);

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    peek(queue);
    dequeue(queue); 
    dequeue(queue);

    printQueue(queue);
}