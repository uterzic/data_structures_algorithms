#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node *next;
    int item;
    int is_char;
} Node;

Node *makeNode(int item, int is_char) {
    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    if (is_char) {
        newNode->item = item;
        newNode->is_char = 1;
    } else {
        newNode->item = item;
        newNode->is_char = 0;
    }
    return newNode;
}

int isEmpty(Node *head) {
    return head == NULL;
}

void push(Node **head, int item, int is_char) {
    Node *newNode = makeNode(item, is_char);
    newNode->next = *head;
    *head = newNode;
}

int pop(Node **head) {
    if (isEmpty(*head)) {
        printf("Can't pop. Stack is empty.\n");
        return -1; // Return an error value.
    }

    Node *temp = *head;
    *head = (*head)->next;

    int result = temp->item;

    free(temp);
    return result;
}

void peek(Node *head) {
    if (isEmpty(head)) {
        printf("Can't peek. Stack is empty.\n");
    }

    if (head->is_char) {
        printf("Peek: %c\n", head->item);
    } else {
        printf("Peek: %d\n", head->item);
    }
}

void printStack(Node *head) {
    if (isEmpty(head)) {
        printf("Can't print. Stack is empty.\n");
        return;
    }

    printf("Stack items: ");
    Node *current = head;
    while (current != NULL) {
        if (current->is_char) {
            printf("%c ", current->item);
        } else {
            printf("%d ", current->item);
        }
        current = current->next;
    }
    printf("\n");
}

char *stringReverser(const char str[]) {
    char result[100];
    Node *strHead = NULL;  // Local head for string reversal

    int i = 0;
    while (str[i] != '\0') {
        push(&strHead, str[i], 1);  // Push each character onto the local stack as integers.
        i++;
    }

    i = 0;
    while (!isEmpty(strHead)) {
        int item = pop(&strHead);
        if (item == -1) {
            // Handle an error condition.
            printf("Error while reversing the string.\n");
            return NULL;
        }

        result[i] = (char)item;
        i++;
    }

    result[i] = '\0';  // Add the null terminator to the reversed string.

    return strdup(result);  // Allocate memory for the reversed string and return it.
}

int main() {
    Node *intCharHead = NULL;  // Head for integer and character items

    push(&intCharHead, 'a', 1);  // Push a character (use 1 to indicate character items).
    push(&intCharHead, 'b', 1);  // Push an integer (use 0 to indicate integer items).
    push(&intCharHead, 'c', 1);  // Push a character (use 1 to indicate character items).
    push(&intCharHead, 95, 0);  // Push an integer (use 0 to indicate integer items).
    printStack(intCharHead);
    peek(intCharHead);
    pop(&intCharHead);
    printStack(intCharHead);

    const char *originalStr = "Hello, World!";
    char *reversedStr = stringReverser(originalStr);

    if (reversedStr != NULL) {
        printf("Reversed String: %s\n", reversedStr);
        free(reversedStr);  // Free the dynamically allocated string.
    }

    return 0;
}
