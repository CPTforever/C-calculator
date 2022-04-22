#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define FORMAT "%s"

typedef char* StackElement;
typedef struct StackObj* Stack;

Stack newStack(void);

void freeStack(Stack* pS);

StackElement getTop(Stack S);

int getHeight(Stack S);

bool isEmpty(Stack S);

void push(Stack S, StackElement data);

void pop(Stack S);

void printStack(Stack S);


