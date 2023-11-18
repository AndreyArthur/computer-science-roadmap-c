#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *previous;
};

struct Stack {
  struct Node *head;
  void(*push)(struct Stack *stack, int value);
  void(*pop)(struct Stack *stack);
  int(*peek)(struct Stack *stack);
  int(*is_empty)(struct Stack *stack);
  int(*size)(struct Stack *stack);
};

struct Node *_create_node(int value) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->value = value;
  return node;
}

int _stack_is_empty(struct Stack *stack) {
  if (stack->head == NULL) {
    return 1;
  } else {
    return 0;
  }
}

int _stack_peek(struct Stack *stack) {
  if (!stack->is_empty(stack)) {
    return stack->head->value;
  }
  return 0;
}

void _stack_push(struct Stack *stack, int value) {
  struct Node *node = _create_node(value);
  if (stack->is_empty(stack)) {
    stack->head = node;
    return;
  }
  node->previous = stack->head;
  stack->head = node;
}

void _stack_pop(struct Stack *stack) {
  if (stack->is_empty(stack)) {
    return;
  }
  if (stack->head->previous == NULL) {
    free(stack->head);
    stack->head = NULL;
    return;
  }
  struct Node *head = stack->head;
  struct Node *node = head->previous;
  stack->head = node;
  free(head);
}

int _stack_size(struct Stack *stack) {
  struct Node *node = stack->head;
  int count = 0;
  while (node != NULL) {
    count++;
    node = node->previous;
  }
  return count;
}

struct Stack *create_stack() {
  struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
  stack->push = &_stack_push;
  stack->pop = &_stack_pop;
  stack->peek = &_stack_peek;
  stack->is_empty = &_stack_is_empty;
  stack->size = &_stack_size;
  return stack;
}
