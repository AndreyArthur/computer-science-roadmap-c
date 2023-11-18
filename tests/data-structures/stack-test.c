#include "../test.c"
#include "../../data-structures/stack.c"

int test_create_stack() {
  struct Stack *stack = create_stack();

  return (stack != NULL);
}

int test_stack_push() {
  struct Stack *stack = create_stack();
  stack->push(stack, 1);
  stack->push(stack, 2);
  stack->push(stack, 3);

  return (
    stack->head->value == 3
      && stack->head->previous->value == 2
      && stack->head->previous->previous->value == 1
  );
}

int test_stack_peek() {
  struct Stack *stack = create_stack();
  stack->push(stack, 1);
  stack->push(stack, 2);
  stack->push(stack, 3);

  return (stack->peek(stack) == 3);
}

int test_stack_is_empty() {
  struct Stack *stack = create_stack();
  int was_empty = stack->is_empty(stack);
  stack->push(stack, 1);
  int is_empty = stack->is_empty(stack);

  return (was_empty == 1 && is_empty == 0);
}

int test_stack_pop() {
  struct Stack *stack_with_one_item = create_stack();
  stack_with_one_item->push(stack_with_one_item, 1);
  struct Stack *stack_with_two_items = create_stack();
  stack_with_two_items->push(stack_with_two_items, 1);
  stack_with_two_items->push(stack_with_two_items, 2);

  stack_with_one_item->pop(stack_with_one_item);
  stack_with_two_items->pop(stack_with_two_items);

  return (
    stack_with_one_item->head == NULL
      && stack_with_two_items->head->value == 1
  );
}

int test_stack_size() {
  struct Stack *stack = create_stack();
  stack->push(stack, 1);
  stack->push(stack, 2);
  stack->push(stack, 3);

  return (stack->size(stack) == 3);
}

int main() {
  struct TestRunner *test = describe("stack");
  test->it("should create a stack", &test_create_stack);
  test->it("should push values to the stack", &test_stack_push);
  test->it("should peek value at the top of the stack", &test_stack_peek);
  test->it("should return 1 if stack is empty and 0 if it's not empty", &test_stack_is_empty);
  test->it("should delete the head of the stack", &test_stack_pop);
  test->it("should return how many items are in the stack", &test_stack_size);
  test->end(test);
}
