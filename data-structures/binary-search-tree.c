#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;

  struct Node *left;
  struct Node *right;
};

struct BinaryTree {
  struct Node *head;
  void(*insert)(struct BinaryTree *tree, int value);
  void(*delete)(struct BinaryTree *tree, int value);
  struct Node *(*search)(struct BinaryTree *tree, int value);
  int *(*traversal)(struct BinaryTree *tree);
  int(*size)(struct BinaryTree *tree);
  int(*height)(struct BinaryTree *tree);
};

static struct Node *create_node(int value) {
  struct Node *node = malloc(sizeof(struct Node));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

static void binary_tree_insert(struct BinaryTree *tree, int value) {
  if (tree->head == NULL) {
    tree->head = create_node(value);
    return;
  }
  struct Node *node = tree->head;
  while (1) {
    if (value <= node->value) {
      if (node->left == NULL) {
        node->left = create_node(value);
        return;
      }
      node = node->left;
    } else {
      if (node->right == NULL) {
        node->right = create_node(value);
        return;
      }
      node = node->right;
    }
  }
}

static void binary_tree_delete_node(struct Node *node, struct Node *previous) {
  if (node->value <= previous->value) {
    if (node->left == NULL && node->right == NULL) {
      previous->left = NULL;
      free(node);
      node = NULL;
      return;
    }
    if (node->right == NULL) {
      previous->left = node->left;
      free(node);
      node = NULL;
      return;
    }
    if (node->left == NULL) {
      previous->left = node->right;
      free(node);
      node = NULL;
      return;
    }
    previous->left = node->right;
    struct Node *left_node = node->left;
    struct Node *right_node = node->right;
    while (right_node->left != NULL) {
      right_node = right_node->left;
    }
    right_node->left = left_node;
    free(node);
    node = NULL;
  } else {
    if (node->left == NULL && node->right == NULL) {
      previous->right = NULL;
      free(node);
      node = NULL;
      return;
    }
    if (node->right == NULL) {
      previous->right = node->left;
      free(node);
      node = NULL;
      return;
    }
    if (node->left == NULL) {
      previous->right = node->right;
      free(node);
      node = NULL;
      return;
    }
    previous->right = node->left;
    struct Node *right_node = node->right;
    struct Node *left_node = node->left;
    while (left_node->right != NULL) {
      left_node = left_node->right;
    }
    left_node->right = right_node;
    free(node);
    node = NULL;
  }
}

static void binary_tree_delete(struct BinaryTree *tree, int value) {
  if (tree->head == NULL) {
    return;
  }
  struct Node *previous = NULL;
  struct Node *node = tree->head;
  while (1) {
    if (node == NULL) {
      return;
    }
    if (node->value == value) {
      binary_tree_delete_node(node, previous);
      return;
    }
    previous = node;
    if (value <= node->value) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
}

static struct Node *binary_tree_search(struct BinaryTree *tree, int value) {
  struct Node *node = tree->head;
  while (1) {
    if (node == NULL) {
      return NULL;
    }
    if (value == node->value) {
      return node;
    }
    if (value < node->value) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
}

void binary_tree_traversal_recursion(
  struct Node *node, int *array, int *current
) {
  if (node) {
    binary_tree_traversal_recursion(node->left, array, current);
    array[*current] = node->value;
    (*current)++;
    binary_tree_traversal_recursion(node->right, array, current);
  }
}

static int *binary_tree_traversal(struct BinaryTree *tree) {
  int size = tree->size(tree);
  int *array = malloc(sizeof(int) * size);
  int current = 0;
  binary_tree_traversal_recursion(tree->head, array, &current);
  return array;
}

static void binary_tree_size_recursion(struct Node *node, int *size) {
  if (node) {
    binary_tree_size_recursion(node->left, size);
    (*size)++;
    binary_tree_size_recursion(node->right, size);
  }
}

static int binary_tree_size(struct BinaryTree *tree) {
  int size = 0;
  binary_tree_size_recursion(tree->head, &size);
  return size;
}

static int binary_tree_height_recursion(struct Node *node) {
  if (node == NULL) {
    return 0;
  }
  int left_height = binary_tree_height_recursion(node->left);
  int right_height = binary_tree_height_recursion(node->right);
  return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

static int binary_tree_height(struct BinaryTree *tree) {
  return binary_tree_height_recursion(tree->head);
}

struct BinaryTree *create_binary_tree() {
  struct BinaryTree *tree = malloc(sizeof(struct BinaryTree));
  tree->insert = &binary_tree_insert;
  tree->delete = &binary_tree_delete;
  tree->search = &binary_tree_search;
  tree->traversal = &binary_tree_traversal;
  tree->size = &binary_tree_size;
  tree->height = &binary_tree_height;
  return tree;
}


