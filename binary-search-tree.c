#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *leftChild;
    struct node *rightChild;
} Node;

Node *makeNode(int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

void insert(Node **root, int value)
{
    Node *newNode = makeNode(value);

    if (*root == NULL)
    {
        *root = newNode;
        return;
    }

    if ((*root)->value > value)
        insert(&((*root)->leftChild), value);

    else if ((*root)->value < value)
        insert(&((*root)->rightChild), value);
}

void printTreePreOrder(Node **root)
{
    if (*root == NULL)
        return;

    printf("%d ", (*root)->value);
    printTreePreOrder(&(*root)->leftChild);
    printTreePreOrder(&(*root)->rightChild);
}

int main()
{
    Node *root = NULL;

    insert(&root,20);
    insert(&root, 30);
    insert(&root, 10);
    printTreePreOrder(&root);
}