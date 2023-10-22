#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Define a structure for the trie node.
typedef struct TrieNode {
    char value;
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode *makeTrieNode(char ch) {
    TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
    newNode->value = ch;
    newNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

int hashFunction(char ch) {
    return ch - 'a';
}

bool hasChild(TrieNode *node, char ch) {
    return node->children[hashFunction(ch)] != NULL;
}

void addChild(TrieNode *node, char ch) {
    node->children[hashFunction(ch)] = makeTrieNode(ch);
}

TrieNode *getChild(TrieNode *node, char ch) {
    return node->children[hashFunction(ch)];
}

typedef struct {
    TrieNode *list[ALPHABET_SIZE];
    size_t size;
} NodesList;

NodesList *getChildren(TrieNode *node) {
    NodesList *list = (NodesList *)malloc(sizeof(NodesList));
    list->size = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            list->list[list->size] = node->children[i];
            list->size++;
        }
    }

    return list;
}

bool hasChildren(TrieNode *node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            return true;
        }
    }
    return false;
}

void removeChild(TrieNode *node, char ch) {
    free(node->children[hashFunction(ch)]);
    node->children[hashFunction(ch)] = NULL;
}

bool contains(TrieNode *root, const char *word) {
    if (word == NULL) {
        return false;
    }

    TrieNode *current = root;
    size_t wordSize = strlen(word);

    for (size_t i = 0; i < wordSize; i++) {
        if (!hasChild(current, word[i])) {
            return false;
        }
        current = getChild(current, word[i]);
    }
    return current->isEndOfWord && word[wordSize] == '\0';
}

void insert(TrieNode *root, const char *word) {
    TrieNode *current = root;
    size_t wordSize = strlen(word);
    for (size_t i = 0; i < wordSize; i++) {
        if (!hasChild(current, word[i])) {
            addChild(current, word[i]);
        }
        current = getChild(current, word[i]);
    }
    current->isEndOfWord = true;
}

void traverse(TrieNode *root) {
    printf("%c\n", root->value);

    NodesList *list = getChildren(root);
    for (size_t i = 0; i < list->size; i++) {
        traverse(list->list[i]);
    }
}

void removeWord(TrieNode *root, const char *word, int index) {
    if (word == NULL) {
        return;
    }

    size_t wordSize = strlen(word);
    if (index == wordSize) {
        root->isEndOfWord = false;
        return;
    }

    char ch = word[index];
    TrieNode *child = getChild(root, ch);

    if (child == NULL) {
        return;
    }

    removeWord(child, word, index + 1);

    if (!hasChildren(child) && !child->isEndOfWord) {
        removeChild(root, ch);
    }
}

// Define a structure for the list node.
typedef struct ListNode {
    char *data;
    struct ListNode *next;
} ListNode;

// Define a structure for the list itself.
typedef struct List {
    ListNode *head;
} List;

// Function to create an empty list.
List *createList() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed for the list.\n");
        exit(1);
    }
    list->head = NULL;
    return list;
}

// Function to add an element to the list.
void listAdd(List *list, const char *data) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for a new list node.\n");
        exit(1);
    }
    newNode->data = strdup(data);
    newNode->next = NULL;

    // If the list is empty, make the new node the head.
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        // Otherwise, add the new node to the end of the list.
        ListNode *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to find the last node of the given prefix.
TrieNode *findLastNodeOf(TrieNode *root, const char *prefix) {
    if (prefix == NULL) {
        return NULL;
    }

    TrieNode *current = root;
    size_t prefixLength = strlen(prefix);
    for (size_t i = 0; i < prefixLength; i++) {
        int index = hashFunction(prefix[i]);
        if (current->children[index] == NULL) {
            return NULL;
        }
        current = current->children[index];
    }
    return current;
}


// Function to free the memory allocated for the list.
void freeList(List *list) {
    ListNode *current = list->head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current->data); // Free the data associated with the list node.
        free(current);       // Free the list node itself.
        current = next;
    }
    free(list); // Finally, free the list structure itself.
}

// Function to find words with the given prefix and add them to the list.
void findWords(TrieNode *root, const char *prefix, List *words) {
    if (root == NULL) {
        return;
    }

    if (root->isEndOfWord) {
        listAdd(words, prefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            char ch[2] = {root->children[i]->value, '\0'};
            char *newPrefix = (char *)malloc(strlen(prefix) + 2); // Allocate memory for the new prefix.
            if (newPrefix == NULL) {
                fprintf(stderr, "Memory allocation failed for a new prefix.\n");
                exit(1);
            }
            strcpy(newPrefix, prefix);
            strcat(newPrefix, ch);
            findWords(root->children[i], newPrefix, words);
            free(newPrefix); // Free the allocated memory for the new prefix.
        }
    }
}

// Function to find words with a given prefix and return them in a list.
List *findWordsWithPrefix(TrieNode *root, const char *prefix) {
    List *words = createList(); // Create a list to store the words.
    TrieNode *lastNode = findLastNodeOf(root, prefix); // Find the last node of the prefix.
    findWords(lastNode, prefix, words); // Find words with the given prefix and add them to the list.
    return words;
}

int main() {
    TrieNode *root = makeTrieNode(' ');

    // Insert words into the trie
    insert(root, "uros");
    insert(root, "urosterzic");
    insert(root, "urosterza");

    printf("Does contains word uros: %d\n", contains(root, "uros"));

    // Find words with a given prefix and print them
    List *wordsWithPrefix = findWordsWithPrefix(root, "uro");
    ListNode *current = wordsWithPrefix->head;
    while (current != NULL) {
        printf("Word with prefix: %s\n", current->data);
        current = current->next;
    }

    // Free the memory used by the list of words with the prefix
    freeList(wordsWithPrefix);

    // Clean up and free the trie
    // ...

    return 0;
}
