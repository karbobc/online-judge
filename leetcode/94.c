#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1e3 + 2
#define log(S, ...) printf(S, ##__VA_ARGS__)

typedef struct TreeNode TreeNode;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

typedef struct Stack Stack;
struct Stack {
    TreeNode* val;
    Stack* next;
};

/**
 * DFS traversal the binary tree.
 */
void dfs(TreeNode* node, int* returnSize, int* arr) {
    if (node == NULL) {
        return;
    }
    dfs(node->left, returnSize, arr);
    arr[(*returnSize)++] = node->val;
    dfs(node->right, returnSize, arr);

}

/**
 * In-Order traversal the binary tree.
 */
int* inorderTraversal(TreeNode* root, int* returnSize) {
    *returnSize = 0;
    int* arr = (int*) malloc(MAX_SIZE * sizeof(int));
    dfs(root, returnSize, arr);
    return arr;
}

/**
 * Build the binary tree.
 */
TreeNode* buildTree() {
    TreeNode* root = NULL;
    char* s = (char*) malloc(MAX_SIZE * sizeof(char));
    scanf("%s", s);
    //  NULL point is returned when the s string is #
    if (strcmp(s, "#") != 0) {
        root = (TreeNode*) malloc(sizeof(TreeNode));
        root->val = atoi(s);
        root->left = buildTree();
        root->right = buildTree();
    }
    free(s);
    return root;
}

/**
 * Push a tree node to the stack.
 */
void push(Stack* stack, TreeNode* val) {
    Stack* node = (Stack*) calloc(1, sizeof(Stack));
    node->val = val;
    node->next = stack->next;
    stack->next = node;
}

/**
 * Pop a tree node from the stack.
 */
TreeNode* pop(Stack* stack) {
    if (stack->next == NULL) {
        return NULL;
    }
    Stack* node = stack->next;
    TreeNode* val = node->val;
    stack->next = node->next;
    free(node);
    return val;
}

/**
 * true is returned when the stack is empty, otherwise, false is returned.
 */
bool isEmpty(Stack* stack) {
    return stack->next == NULL;
}

int main() {
    // define
    int* returnSize;
    int* arr;
    TreeNode* root = buildTree();
    Stack* stack = (Stack*) calloc(1, sizeof(Stack));
    // output
    arr = inorderTraversal(root, returnSize);
    for (int i = 0; i < *returnSize; i++) {
        log("%d\n", arr[i]);
    }
    // free memory
    free(arr);
    while (root != NULL) {
        // push the left tree node into the stack
        while (root != NULL) {
            push(stack, root);
            root = root->left;
        }
        // pop a tree node when the stack is not empty
        if (!isEmpty(stack)) {
            root = pop(stack);
            // free memory for a tree node
            while (root->right == NULL && !isEmpty(stack)) {
                free(root);
                root = pop(stack);
            }
            root = root->right;
        }
    }
    free(stack);
    return 0;
}
