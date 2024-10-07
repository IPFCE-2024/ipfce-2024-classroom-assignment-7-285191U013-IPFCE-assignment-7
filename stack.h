#pragma once

#include <stdbool.h>

typedef struct node {
  int data;
  struct node *next;
} node;

typedef struct {
  node *head;
} stack;

void initialize(stack *s);
void push(int element, stack *s);
int pop(stack *s);
bool empty(stack *s);
bool full(stack *s);
