#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *next;
};

struct List {
  struct Node *head;
  struct Node *(*get)(struct List *list, int position);
  void(*push)(struct List *list, int value);
  void(*unshift)(struct List *list, int value);
  void(*insert)(struct List *list, int position, int value);
  void(*delete)(struct List *list, int position);
  int(*length)(struct List *list);
  void(*print)(struct List *list);
  void(*free)(struct List *list);
  void(*concat)(struct List *first_list, struct List *second_list);
  void(*reverse)(struct List *list);
};

struct Node *create_node(int value) {
  struct Node *node = malloc(sizeof(struct Node));
  node->value = value;
  return node;
}

static struct Node *list_get(struct List *list, int position) {
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

static void list_push(struct List *list, int value) {
  struct Node *node = list->head;
  while (node->next != NULL) {
    node = node->next;
  }
  node->next = create_node(value);
}

static void list_unshift(struct List *list, int value) {
  struct Node *node = create_node(value);
  node->next = list->head;
  list->head = node;
}

static void list_insert(struct List *list, int position, int value) {
  if (position <= 0) {
    list->unshift(list, value);
    return;
  }
  struct Node *node_before_position = list_get(list, position - 1);
  if (node_before_position == NULL || node_before_position->next == NULL) {
    list->push(list, value);
    return;
  }
  struct Node *node_to_be_inserted = create_node(value);
  node_to_be_inserted->next = node_before_position->next;
  node_before_position->next = node_to_be_inserted;
}

static void list_delete(struct List *list, int position) {
  if (position < 0) {
    return;
  }
  if (position == 0) {
    struct Node *head = list->head;
    list->head = list->head->next;
    free(head);
    return;
  }
  struct Node *node_before_position = list->get(list, position - 1);
  if (node_before_position == NULL || node_before_position->next == NULL) {
    return;
  }
  struct Node *node_to_be_deleted = node_before_position->next;
  node_before_position->next = node_to_be_deleted->next;
  free(node_to_be_deleted);
}

static int list_length(struct List *list) {
  struct Node *node = list->head;
  int count = 0;
  while (node != NULL) {
    count++;
    node = node->next;
  }
  return count;
}

static void list_print(struct List *list) {
  for (int index = 0; index < list->length(list); index++) {
    printf("[%d]->%d\n", index, list->get(list, index)->value);
  }
}

static void list_free(struct List *list) {
  int list_length = list->length(list);
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

static struct Node *list_reverse_recursion(
  struct Node *node,
  struct Node *previous
) {
  if (node == NULL) {
    return previous;
  }
  struct Node *next_node = node->next;
  node->next = previous;
  return list_reverse_recursion(next_node, node);
}

static void list_reverse(struct List *list) {
  struct Node *head = list_reverse_recursion(list->head, NULL);
  list->head = head;
}

static void list_concat(struct List *first_list, struct List *second_list) {
  struct Node *node = first_list->head;
  while (node->next != NULL) {
    node = node->next;
  }
  node->next = second_list->head;
}

struct List *create_list(struct Node *head) {
  struct List *list = malloc(sizeof(struct List));
  list->head = head;
  list->get = &list_get;
  list->push = &list_push;
  list->unshift = &list_unshift;
  list->insert = &list_insert;
  list->delete = &list_delete;
  list->length = &list_length;
  list->print = &list_print;
  list->free = &list_free;
  list->reverse = &list_reverse;
  list->concat = &list_concat;
  return list;
}
