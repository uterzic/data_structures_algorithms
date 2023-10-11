#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node
{
    int value;
    struct node *leftChild;
    struct node *rightChild;
} Node;

typedef struct list
{
    int *elements;
    int length;
} List;

bool isLeaf(Node *node);
int height(Node *node);

int max(int a, int b) {
    return (a > b) ? a : b;
}
List *makeList()
{
    List *newList = malloc(sizeof(List));
    newList->elements = calloc(100, sizeof(int));
    newList->length = 0;

    return newList;
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

void addToList(List *list, int value)
{
    list->elements[list->length++] = value;
}

void getNodesAtDistance(Node *root, int distance, List *list)
{
    if (root == NULL)
    {
        return;
    }

    if (distance == 0)
    {
        addToList(list, root->value);
    }

    getNodesAtDistance(root->leftChild, distance - 1, list);
    getNodesAtDistance(root->rightChild, distance - 1, list);
}

List *getNodesWithDistance(Node* root, int distance)
{
    List *list = makeList();
    getNodesAtDistance(root, distance, list);

    return list;
}

void printList(List *list)
{
    printf("List has:");
    for (int i = 0; i < list->length; i++)
    {
        printf(" %d", list->elements[i]);
    }
    printf("\n");
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

void freeList(List *list)
{
    free(list->elements);  // Free the array of elements
    free(list);            // Free the List structure
}

void traversLevelOrder(Node *root)
{
    printf("Traversing tree:\n");
    for (int level = 0; level < height(root); level++)
    {
        List *list = getNodesWithDistance(root, level);
        printf("Level [%d] has:", level);
        for (int nodeIndex = 0; nodeIndex < list->length; nodeIndex++)
        {
            printf(" %d", list->elements[nodeIndex]);
        }
        printf("\n");

        freeList(list);
    }
}

bool isBinarySearchUtil(Node *root, int min, int max)
{
    if (root == NULL)
        return true;

    if (root->value < min && root->value > max)
        return false;

    return isBinarySearchUtil(root->leftChild, min, root->value - 1) &&
            isBinarySearchUtil(root->rightChild, root->value + 1, max);
}

bool isBinarySearchTree(Node *root)
{
    printf("Is this tree BST: %s\n", isBinarySearchUtil(root, INT_MIN, INT_MAX) ? "Yes" : "No");
}

// TODO: make function for deleting node.

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
    printf("Tree has value 20: %s\n", hasValue(root, 20) ? "Yes" : "No");

    List *list = getNodesWithDistance(root, 1);
    printList(list);
    traversLevelOrder(root);
    isBinarySearchTree(root);
}