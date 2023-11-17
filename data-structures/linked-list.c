#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *next;
};

struct List {
  struct Node *head;
};

struct List *new_list(struct Node *head) {
  struct List *list = malloc(sizeof(struct List));
  list->head = head;
  return list;
}

struct Node *new_node(int value) {
  struct Node *node = malloc(sizeof(struct Node));
  node->value = value;
  return node;
}

struct Node *get(struct List *list, int position) {
  if (position < 0) {
    return NULL;
  }
  if (position == 0) {
    return list->head;
  }
  struct Node *node = list->head;
  for (int index = 0; index < position; index++) {
    if (node->next == NULL) {
      return NULL;
    }
    node = node->next;
  }
  return node;
}

void push(struct List *list, int value) {
  struct Node *node = list->head;
  while (node->next != NULL) {
    node = node->next;
  }
  node->next = new_node(value);
}

void unshift(struct List *list, int value) {
  struct Node *node = new_node(value);
  node->next = list->head;
  list->head = node;
}

void insert(struct List *list, int position, int value) {
  if (position <= 0) {
    unshift(list, value);
    return;
  }
  struct Node *node_before_position = get(list, position - 1);
  if (node_before_position == NULL || node_before_position->next == NULL) {
    push(list, value);
    return;
  }
  struct Node *node_to_be_inserted = new_node(value);
  node_to_be_inserted->next = node_before_position->next;
  node_before_position->next = node_to_be_inserted;
}

void delete(struct List *list, int position) {
  if (position < 0) {
    return;
  }
  if (position == 0) {
    struct Node *head = list->head;
    list->head = list->head->next;
    free(head);
    return;
  }
  struct Node *node_before_position = get(list, position - 1);
  if (node_before_position == NULL || node_before_position->next == NULL) {
    return;
  }
  struct Node *node_to_be_deleted = node_before_position->next;
  node_before_position->next = node_to_be_deleted->next;
  free(node_to_be_deleted);
}

int length(struct List *list) {
  struct Node *node = list->head;
  int count = 0;
  while (node != NULL) {
    count++;
    node = node->next;
  }
  return count;
}

void print(struct List *list) {
  for (int index = 0; index < length(list); index++) {
    printf("[%d]->%d\n", index, get(list, index)->value);
  }
}

void free_list(struct List *list) {
  int list_length = length(list);
  struct Node *node = list->head;
  int count = 0;
  while (node != NULL) {
    struct Node *temp_node = node;
    node = node->next;
    free(temp_node);
    count++;
  }
  free(list);
}

void reverse(struct List *list) {
  struct Node *prev, *current, *next;
  prev = NULL;
  current = list->head;
  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  list->head = prev;
}

void concat(struct List *first_list, struct List *second_list) {
  struct Node *node = first_list->head;
  while (node->next != NULL) {
    node = node->next;
  }
  node->next = second_list->head;
}

int main() {
  struct List *list = new_list(new_node(1));
  push(list, 2);
  push(list, 3);
  struct List *second_list = new_list(new_node(4));
  push(second_list, 5);
  push(second_list, 6);
  concat(list, second_list);
  reverse(list);
  print(list);
  free_list(list);
}
