#include "../test.c"
#include "../../data-structures/linked-list.c"

int test_create_node() {
  struct Node *node = create_node(1);

  return (node->value == 1 && node->next == NULL);
}

int test_create_list() {
  struct Node *head = create_node(1);
  struct List *list = create_list(head);

  return (list->head->value == head->value);
}

int test_list_get() {
  struct List *list = create_list(create_node(1));
  list->push(list, 2);
  list->push(list, 3);

  return (list->get(list, 2)->value == 3);
}

int test_list_push() {
  struct List *list = create_list(create_node(1));
  list->push(list, 2);
  list->push(list, 3);

  return (
    list->head->value == 1
      && list->head->next->value == 2
      && list->head->next->next->value == 3
  );
}

int test_list_unshift() {
  struct List *list = create_list(create_node(3));
  list->unshift(list, 2);
  list->unshift(list, 1);

  return (
    list->head->value == 1
      && list->head->next->value == 2
      && list->head->next->next->value == 3
  );
}

int test_list_insert() {
  struct List *list = create_list(create_node(1));
  list->push(list, 3);
  list->insert(list, 1, 2);

  return (
    list->head->value == 1
      && list->head->next->value == 2
      && list->head->next->next->value == 3
  );
}

int test_list_delete() {
  struct List *list = create_list(create_node(1));
  list->push(list, 2);
  list->push(list, 3);
  list->delete(list, 2);

  return (
    list->head->value == 1
      && list->head->next->value == 2
      && list->head->next->next == NULL
  );
}

int test_list_length() {
  struct List *list = create_list(create_node(1));
  list->push(list, 2);
  list->push(list, 3);

  return (list->length(list) == 3);
}

int test_list_concat() {
  struct List *list = create_list(create_node(1));
  list->push(list, 2);
  list->push(list, 3);
  struct List *second_list = create_list(create_node(4));
  second_list->push(second_list, 5);
  second_list->push(second_list, 6);
  list->concat(list, second_list);

  return (list->length(list) == 6 && list->get(list, 3)->value == 4);
}

int test_list_reverse() {
  struct List *list = create_list(create_node(1));
  list->push(list, 2);
  list->push(list, 3);
  list->reverse(list);

  return (
    list->head->value == 3
      && list->head->next->value == 2
      && list->head->next->next->value == 1
  );
}

int main() {
  struct TestRunner *test = describe("linked list");
  test->it("should create a node", &test_create_node);
  test->it("should create a linked list", &test_create_list);
  test->it("should get a node of a list by position", &test_list_get);
  test->it("should push to the end of a linked list", &test_list_push);
  test->it("should unshift to the start of a linked list", &test_list_unshift);
  test->it("should insert to the middle of a linked list", &test_list_insert);
  test->it("should delete a node a linked list", &test_list_delete);
  test->it("should get the length of a linked list", &test_list_length);
  test->it("should concatenate two linked lists", &test_list_concat);
  test->it("should reverse a linked list", &test_list_reverse);
  test->end(test);
}
