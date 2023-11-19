#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

struct Node {
  char *key;
  char *value;
  struct Node *next;
};

struct HashTable {
  struct Node *list[HASH_SIZE];
  void(*set)(struct HashTable *hashtable, char *key, char *value);
  char *(*get)(struct HashTable *hashtable, char *key);
  void (*delete)(struct HashTable *hashtable, char *key);
  int(*contains)(struct HashTable *hashtable, char *key);
};

int _djb2(char *key) {
  int hash_number = 5381;
  char current_character = '1';
  for (int index = 0; current_character; index++) {
    current_character = key[index];
    hash_number = (hash_number * 33) + current_character;
  }
  return hash_number % HASH_SIZE;
}

struct Node *_create_node(char *key, char *value) {
  struct Node *node = malloc(sizeof(struct Node));
  node->key = key;
  node->value = value;
  return node;
}

void _hashtable_set(struct HashTable *hashtable, char *key, char *value) {
  int position = _djb2(key);
  if (hashtable->list[position] == NULL) {
    hashtable->list[position] = _create_node(key, value);
    return;
  }
  struct Node *node = hashtable->list[position];
  struct Node *previous = NULL;
  while (node != NULL) {
    int same_key = strcmp(node->key, key) == 0;
    if (same_key) {
      node->value = value;
      return;
    }
    previous = node;
    node = node->next;
  }
  previous->next = _create_node(key, value);
}

char *_hashtable_get(struct HashTable *hashtable, char *key) {
  int position = _djb2(key);
  if (hashtable->list[position] == NULL) {
    return "";
  }
  struct Node *node = hashtable->list[position];
  while (node != NULL) {
    int same_key = strcmp(node->key, key) == 0;
    if (same_key) {
      return node->value;
    }
    node = node->next;
  }
  return "";
}

void _hashtable_delete(struct HashTable *hashtable, char *key) {
  int position = _djb2(key);
  if (hashtable->list[position] == NULL) {
    return;
  }
  struct Node *node = hashtable->list[position];
  struct Node *previous = NULL;
  while (node != NULL) {
    int same_key = strcmp(node->key, key) == 0;
    if (!same_key) {
      previous = node;
      node = node->next;
      continue;
    }
    if (node->next == NULL) {
      if (previous == NULL) {
        free(node);
        node = NULL;
        hashtable->list[position] = NULL;
        return;
      }
      previous->next = NULL;
      free(node);
      node = NULL;
      return;
    }
    if (previous == NULL) {
      hashtable->list[position] = node->next;
    } else {
      previous->next = node->next;
    }
    free(node);
    node = NULL;
    return;
  }
}

int _hashtable_contains(struct HashTable *hashtable, char *key) {
  int position = _djb2(key);
  if (hashtable->list[position] == NULL) {
    return 0;
  }
  struct Node *node = hashtable->list[position];
  while (node != NULL) {
    int same_key = strcmp(node->key, key) == 0;
    if (same_key) {
      return 1;
    }
    node = node->next;
  }
  return 0;
}

struct HashTable *create_hashtable() {
  struct HashTable *hashtable = malloc(sizeof(struct HashTable));
  hashtable->set = &_hashtable_set;
  hashtable->get = &_hashtable_get;
  hashtable->delete = &_hashtable_delete;
  hashtable->contains = &_hashtable_contains;
  return hashtable;
}

