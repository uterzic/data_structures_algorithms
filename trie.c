#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct node
{
    char value;
    struct node *children[ALPHABET_SIZE];
    bool isEndOfWord;
} Node;

Node *makeNode(char ch)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value = ch;
    newNode->isEndOfWord = false;

    return newNode;
}

int hashFunction(char ch)
{
    return ch - 'a';
}

bool hasChild(Node *node, char ch)
{
    return node->children[hashFunction(ch)] != NULL;
}

void addChild(Node *node, char ch)
{
    Node *newChild = malloc(sizeof(Node));
    node->children[hashFunction(ch)] = newChild;
    newChild->value = ch;
}

Node *getChild(Node *node, char ch)
{
    return node->children[hashFunction(ch)];
}

typedef struct {
    Node *list[ALPHABET_SIZE];
    size_t size;
} NodesList;

NodesList *getChildren(Node* node)
{
    NodesList *list = malloc(sizeof(NodesList));
    list->size = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            list->list[list->size] = node->children[i];
            list->size++;
        }
    }

    return list;
}

bool hasChildren(Node *node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
            return true;
    }
    return false;
}

void removeChild(Node *node, char ch)
{
    Node *child = node->children[hashFunction(ch)];
    node->children[hashFunction(ch)] = NULL;
    free(child);
}

bool contains(Node *root, char word[])
{
    if (word == NULL)
        return false;

    Node *current = root;
    size_t wordSize = strlen(word);

    for (int i = 0; i < wordSize; i++)
    {
        if (!hasChild(current, word[i]))
            return false;
        current = getChild(current, word[i]);
    }
    return current->isEndOfWord && word[wordSize] =='\0';
}

void insert(Node *root, char word[])
{
    Node *current = root;
    size_t wordSize = strlen(word);
    for (int i = 0; i < wordSize; i++)
    {
        if (!hasChild(current, word[i]))
            addChild(current, word[i]);
        current = getChild(current, word[i]);
    }
    current->isEndOfWord = true;
}

void traverse(Node *root) {
    printf("%c\n", root->value);

    NodesList *list = getChildren(root);
    for (int i = 0; i < list->size; i++)
        traverse(list->list[i]);
}


int main()
{
    Node *root = makeNode(' ');

    insert(root, "uros");
    insert(root, "urose");
    insert(root, "urom");

    traverse(root);
}