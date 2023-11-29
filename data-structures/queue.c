#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *next;
};

struct Queue {
  struct Node *tail;
  void(*enqueue)(struct Queue *queue, int value);
  int(*is_empty)(struct Queue *queue);
  int(*peek)(struct Queue *queue);
  void(*dequeue)(struct Queue *queue);
  int(*size)(struct Queue *queue);
};

static struct Node *create_node(int value) {
  struct Node *node = malloc(sizeof(struct Node));
  node->value = value;
  return node;
}

static int queue_is_empty(struct Queue *queue) {
  if (queue->tail == NULL) {
    return 1;
  }
  return 0;
}

static void queue_enqueue(struct Queue *queue, int value) {
  struct Node *node = create_node(value);
  if (queue->is_empty(queue)) {
    queue->tail = node;
    return;
  }
  node->next = queue->tail;
  queue->tail = node;
}

static int queue_peek(struct Queue *queue) {
  if (queue->is_empty(queue)) {
    return 0;
  }
  struct Node *node = queue->tail;
  while (node->next != NULL) {
    node = node->next;
  }
  return node->value;
}

static void queue_dequeue(struct Queue *queue) {
  if (queue->is_empty(queue)) {
    return;
  }
  struct Node *node = queue->tail;
  struct Node *previous = NULL;
  while (node->next != NULL) {
    previous = node;
    node = node->next;
  }
  if (previous == NULL) {
    free(node);
    node = NULL;
    return;
  }
  previous->next = NULL;
  free(node);
  node = NULL;
}

static int queue_size(struct Queue *queue) {
  int count = 0;
  struct Node *node = queue->tail;
  while (node != NULL) {
    count++;
    node = node->next;
  }
  return count;
}

struct Queue *create_queue() {
  struct Queue *queue = malloc(sizeof(struct Queue));
  queue->is_empty = &queue_is_empty;
  queue->enqueue = &queue_enqueue;
  queue->peek = &queue_peek;
  queue->dequeue = &queue_dequeue;
  queue->size = &queue_size;
  return queue;
}

