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
  void(*free)(struct Stack *stack);
};

static struct Node *create_node(int value) {
  struct Node *node = malloc(sizeof(struct Node));
  node->value = value;
  return node;
}

static int stack_is_empty(struct Stack *stack) {
  if (stack->head == NULL) {
    return 1;
  } else {
    return 0;
  }
}

static int stack_peek(struct Stack *stack) {
  if (!stack->is_empty(stack)) {
    return stack->head->value;
  }
  return 0;
}

static void stack_push(struct Stack *stack, int value) {
  struct Node *node = create_node(value);
  if (stack->is_empty(stack)) {
    stack->head = node;
    return;
  }
  node->previous = stack->head;
  stack->head = node;
}

static void stack_pop(struct Stack *stack) {
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

static int stack_size(struct Stack *stack) {
  struct Node *node = stack->head;
  int count = 0;
  while (node != NULL) {
    count++;
    node = node->previous;
  }
  return count;
}

static void stack_free(struct Stack *stack) {
  int counter = stack->size(stack);
  while (counter > 0) {
    stack->pop(stack);
    counter--;
  }
  free(stack);
}

struct Stack *create_stack() {
  struct Stack *stack = malloc(sizeof(struct Stack));
  stack->push = &stack_push;
  stack->pop = &stack_pop;
  stack->peek = &stack_peek;
  stack->is_empty = &stack_is_empty;
  stack->size = &stack_size;
  stack->free = &stack_free;
  return stack;
}
