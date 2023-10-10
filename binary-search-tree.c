#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int value;
    struct node *leftChild;
    struct node *rightChild;
} Node;

bool isLeaf(Node *node);
int height(Node *node);

int max(int a, int b) {
    return (a > b) ? a : b;
}

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

int height(Node *root)
{
    if (root == NULL)
        return 0;

    if (isLeaf(root))
        return 1;

    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);
    return 1 + max(leftHeight, rightHeight);
}

int minValue(Node *root)
{
    if (root->leftChild == NULL)
        return root->value;

    return minValue(root->leftChild);
}

int maxValue(Node *root)
{
    if (root->rightChild == NULL)
        return root->value;

    return maxValue(root->rightChild);
}

int hasValue(Node *root, int value)
{
    if (root == NULL)
        return false;

    if (root->value == value)
        return true;

    return hasValue(root->leftChild, value) || hasValue(root->rightChild, value);
}

bool isLeaf(Node *node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

void printTreePreOrder(Node *root)
{
    if (root == NULL)
        return;

    printf("%d \n", root->value);
    printTreePreOrder(root->leftChild);
    printTreePreOrder(root->rightChild);
}

int main()
{
    Node *root = NULL;

    insert(&root,20);
    insert(&root, 30);
    insert(&root, 10);
    insert(&root, 5);
    printTreePreOrder(root);
    printf("Heigh of tree is: %d\n", height(root));
    printf("Minimal value in tree is: %d\n", minValue(root));
    printf("Maximal value in tree is: %d\n", maxValue(root));
    printf("Tree has value 20: %s", hasValue(root, 5) ? "Yes\n" : "No\n");
}