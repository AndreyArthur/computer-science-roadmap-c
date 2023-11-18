#include "../test.c"
#include "../../data-structures/linked-list.c"

int test_create_node() {
  struct Node *node = create_node(1);
  return (node->value == 1 && node->next == NULL);
}

int main() {
  struct TestRunner *test = describe("linked list");
  test->it("should create a node successfully", &test_create_node);
  test->end(test);
}
