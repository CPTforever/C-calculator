#include "stack.h"
#include "Error.h"

typedef struct NodeObj* Node; 

typedef struct NodeObj {
    StackElement token; 
    Node next; 
} NodeObj; 

typedef struct StackObj {
    Node top; 
    int height; 
} StackObj; 

Node newNode(StackElement token) {
    Node N = malloc(sizeof(NodeObj));
    N->token = token;
    N->next = NULL;

    return N;
}

void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }

    return;
}

Stack newStack(void) {
    Stack S = malloc(sizeof(StackObj));
    S->top = NULL;
    S->height = 0;

    return S; 
}

void freeStack(Stack *pS) {
    if (pS != NULL && *pS != NULL) {
        while ( !isEmpty(*pS) ) { pop(*pS); }
        free(*pS);
        *pS = NULL;
    }
}
StackElement getTop(Stack S) {
    error(S == NULL, "Stack Error: calling getTop() on NULL stack reference\n");
    error(isEmpty(S), "Stack Error: calling getTop() on empty Stack \n");

    return S->top->token; 
}

int getHeight(Stack S) {
    error(S == NULL, "Stack Error: calling getHeight() on NULL stack reference\n");

    return S->height;
}

bool isEmpty(Stack S) {
    error(S == NULL, "Stack Error: calling isEmpty() on NULL stack reference\n");

    return S->height == 0;
}

void push(Stack S, StackElement token) {
    error(S == NULL, "Stack Error: calling push() on NULL stack reference\n");
    
    Node N = newNode(token);
    if (isEmpty(S)) {
        S->top = N;
    } 
    else {
        N->next = S->top;
        S->top = N;
    }
    S->height++;
}

void pop(Stack S) {
    error(S == NULL, "Stack Error: calling pop() on NULL stack reference\n");
    error(isEmpty(S), "Stack ERror: calling pop() on empty stack\n");

    Node N = S->top;

    if (getHeight(S) > 1) {
        S->top = S->top->next;
    }
    else {
        S->top = NULL;
    }
    S->height--;
    freeNode(&N);

}

