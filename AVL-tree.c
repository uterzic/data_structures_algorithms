#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AVLNode
{
    int height;
    int value;
    struct AVLNode *leftChild;
    struct AVLNode *rightChild;
} AVLNode;

AVLNode *makeAVLNode(int value)
{
    AVLNode *newNode = malloc(sizeof(AVLNode));
    newNode->value = value;
    newNode->height = 0;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;

    return newNode;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(AVLNode *node)
{
    return (node == NULL) ? -1 : node->height;
}

void setHeight(AVLNode *node)
{
    node->height = max(height(node->leftChild), height(node->rightChild) + 1);
}

int balanceFactor(AVLNode *node)
{
    return (node == NULL) ? 0 : height(node->leftChild) - height(node->rightChild);
}

bool isLeftHeavy(AVLNode *node) {
    return balanceFactor(node) > 1;
}

bool isRightHeavy(AVLNode *node) {
    return balanceFactor(node) < -1;
}

AVLNode *rotateLeft(AVLNode *root)
{
    AVLNode *newRoot = root->rightChild;

    root->rightChild = newRoot->leftChild;
    newRoot->leftChild = root;

    setHeight(root);
    setHeight(newRoot);

    return newRoot;
}

AVLNode *rotateRight(AVLNode *root)
{
    AVLNode *newRoot = root->leftChild;

    root->leftChild = newRoot->rightChild;
    newRoot->rightChild = root;

    setHeight(root);
    setHeight(newRoot);

    return newRoot;
}

AVLNode *balance(AVLNode *root)
{
    if (isLeftHeavy(root))
    {
        if (balanceFactor(root->leftChild) < 0)
            root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }
    else if (isRightHeavy(root))
    {
        if (balanceFactor(root->rightChild) > 0)
            root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }

    return root;
}

AVLNode *insertUtil(AVLNode *root, int value)
{
    if (root == NULL)
        return makeAVLNode(value);

    if (value < root->value)
        root->leftChild = insertUtil(root->leftChild, value);
    else
        root->rightChild = insertUtil(root->rightChild, value);

    setHeight(root);

    return balance(root);
}

void printAVLTree(AVLNode *root)
{
    if (root == NULL)
        return;

    printAVLTree(root->leftChild);
    printf("%d ", root->value);
    printAVLTree(root->rightChild);
}

void insert(AVLNode **root, int value)
{
    *root = insertUtil(*root, value);
}

int main()
{
    AVLNode *root = NULL;
    insert(&root, 10);

    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);
    insert(&root, 60);

    printAVLTree(root);
}