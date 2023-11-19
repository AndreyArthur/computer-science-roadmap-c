#include "../test.c"
#include "../../data-structures/queue.c"

int test_create_queue() {
  struct Queue *queue = create_queue();

  return queue != NULL;
}

int test_queue_enqueue() {
  struct Queue *queue = create_queue();
  queue->enqueue(queue, 1);
  queue->enqueue(queue, 2);
  queue->enqueue(queue, 3);

  return (
    queue->tail->value == 3
      && queue->tail->next->value == 2
      && queue->tail->next->next->value == 1
  );
}

int test_queue_peek() {
  struct Queue *queue = create_queue();
  queue->enqueue(queue, 1);
  queue->enqueue(queue, 2);
  queue->enqueue(queue, 3);

  return (queue->peek(queue) == 1);
}

int test_queue_dequeue() {
  struct Queue *queue = create_queue();
  queue->enqueue(queue, 1);
  queue->enqueue(queue, 2);
  queue->enqueue(queue, 3);
  queue->dequeue(queue);

  return (queue->peek(queue) == 2);
}

int test_queue_size() {
  struct Queue *queue = create_queue();
  queue->enqueue(queue, 1);
  queue->enqueue(queue, 2);
  queue->enqueue(queue, 3);

  return (queue->size(queue) == 3);
}

int main() {
  struct TestRunner *test = describe("queue");
  test->it("should create a queue", &test_create_queue);
  test->it("should enqueue items into the queue", &test_queue_enqueue);
  test->it("should get next item in the queue", &test_queue_peek);
  test->it("should dequeue next item in the queue", &test_queue_peek);
  test->it("should get the size of the queue", &test_queue_size);
  test->end(test);
}
