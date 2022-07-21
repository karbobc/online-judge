#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1e4 + 4
#define log(S, ...) printf(S, ##__VA_ARGS__)

typedef struct Stack Stack;
typedef struct Stack Node;
struct Stack {
    char val;
    Stack* next;
};

/**
 * stack push
 */
void push(Stack* stack, char val) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->val = val;
    node->next = stack->next;
    stack->next = node;
}

/**
 * stack pop
 */
char pop(Stack* stack) {
    if (stack->next == NULL) {
        return -1;
    }
    Node* node = stack->next;
    char val = node->val;
    stack->next = node->next;
    free(node);
    return val;
}

/**
 * right bracket is returned when the 'bracket' is left bracket
 */
char pairs(char bracket) {
    if (bracket == '(') {
        return ')';
    }
    if (bracket == '{') {
        return '}';
    }
    if (bracket == '[') {
        return ']';
    }
    return -1;
}

/**
 * Determine whether the string is valid
 * 1. The left bracket must be closed with the same type of right bracket.
 * 2. The left bracket must be closed in the correct order.
 */
bool isValid(char* s) {
    int len = strlen(s);
    // false is returned when the length of string is odd
    if (len & 1) {
        return false;
    }
    Stack* stack = (Stack*) calloc(1, sizeof(Stack));
    for (int i = 0; i < len; i++) {
        // push left bracket when s[i] is left bracket
        if (pairs(s[i]) != -1) {
            push(stack, s[i]);
            continue;
        }
        // pop left bracket when s[i] is right bracket
        char val = pop(stack);
        // false is returned when stack is empty or 
        // the bracket popped by stack not equal with the same bracket
        // but first it need to free memory
        if (val == -1 || pairs(val) != s[i]) {
            while (stack->next != NULL) {
                Node* node = stack->next;
                stack->next = node->next;
                free(node);
            }
            free(stack);
            return false;
        }
    }
    // true is returned when stack is empty
    if (stack->next == NULL) {
        return true;
    }
    // false is returned when stack is not empty, but first it need to free memory
    while (stack->next != NULL) {
        Node* node = stack->next;
        stack->next = node->next;
        free(node);
    }
    free(stack);
    return false;
}

int main() {
    // define
    char* s = (char*) malloc(MAX_SIZE * sizeof(char));
    // input
    scanf("%s", s);
    // output
    puts(isValid(s) ? "true" : "false");
    // free memory
    free(s);
    return 0;
}
