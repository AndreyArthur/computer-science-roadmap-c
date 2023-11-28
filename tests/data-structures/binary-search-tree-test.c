#include "../test.c"
#include "../../data-structures/binary-search-tree.c"

int test_create_bynary_tree() {
  struct BinaryTree *tree = create_binary_tree();

  return (tree != NULL);
}

int test_binary_tree_insert() {
  struct BinaryTree *tree = create_binary_tree();
  tree->insert(tree, 50);
  tree->insert(tree, 49);
  tree->insert(tree, 51);

  return (
    tree->head->value == 50
      && tree->head->left->value == 49
      && tree->head->right->value == 51
  );
}

int test_binary_tree_search() {
  struct BinaryTree *tree = create_binary_tree();
  tree->insert(tree, 50);
  tree->insert(tree, 49);
  tree->insert(tree, 51);

  struct Node *null_node = tree->search(tree, 52);
  struct Node *node = tree->search(tree, 49);

  return (null_node == NULL && node->value == 49);
}

int test_binary_tree_size() {
  struct BinaryTree *tree = create_binary_tree();
  tree->insert(tree, 50);
  tree->insert(tree, 49);
  tree->insert(tree, 51);

  int size = tree->size(tree);

  return (size == 3);
}

int test_binary_tree_traversal() {
  struct BinaryTree *tree = create_binary_tree();
  tree->insert(tree, 50);
  tree->insert(tree, 49);
  tree->insert(tree, 51);

  int *array = tree->traversal(tree);

  return (
    array[0] == 49
      && array[1] == 50
      && array[2] == 51
  );
}

int test_binary_tree_delete() {
  struct BinaryTree *tree = create_binary_tree();
  tree->insert(tree, 50);
  tree->insert(tree, 49);
  tree->insert(tree, 52);
  tree->insert(tree, 51);
  int node_existed = tree->head->right->left->value == 51;

  tree->delete(tree, 51);
  int node_no_more_exists = tree->head->right->left == NULL;

  return (
    node_existed
      && node_no_more_exists
      && tree->search(tree, 51) == NULL
  );
}

int test_binary_tree_height() {
  struct BinaryTree *tree = create_binary_tree();
  tree->insert(tree, 50);
  tree->insert(tree, 49);
  tree->insert(tree, 52);
  tree->insert(tree, 51);

  return tree->height(tree) == 3;
}

int main() {
  struct TestRunner *test = describe("binary tree");
  test->it("should create a binary tree", &test_create_bynary_tree);
  test->it("should insert in binary tree", &test_binary_tree_insert);
  test->it("should search in binary tree", &test_binary_tree_search);
  test->it("should get binary tree size", &test_binary_tree_size);
  test->it("should get binary tree height", &test_binary_tree_height);
  test->it("should return a ordered array from binary tree", &test_binary_tree_traversal);
  test->it("should delete a node from binary tree", &test_binary_tree_delete);
  test->end(test);
}
