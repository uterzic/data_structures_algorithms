#include <stdio.h>
#include <stdlib.h>

#define size 3

typedef struct stack
{
    int items[size];
    int count;
} Stack;

Stack *makeStack()
{
    Stack *newStack = malloc(sizeof(Stack));
    newStack->count = 0;

    return newStack;
}

void push(Stack *stack, int item)
{
    stack->items[stack->count++] = item;
}

int pop(Stack *stack)
{
    return stack->items[--stack->count]; 
}

int peek(Stack *stack)
{
    return stack->items[stack->count - 1];
}

void printStack(Stack *stack)
{
    printf("Items of stack: ");

    for (int i = 0; i < stack->count; i++)
    {
        printf("%d ", stack->items[i]);
    }

    printf("\n");
}

int main()
{
    Stack *stack = makeStack();

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    printf("Peek: %d\n", peek(stack));

    printStack(stack);

    pop(stack);
    printStack(stack);
}