#include "../test.c"
#include "../../data-structures/hashtable.c"
#include <string.h>

int test_create_hashtable() {
  struct HashTable *hashtable = create_hashtable();

  return (hashtable != NULL);
}

int test_hashtable_set_and_get() {
  struct HashTable *hashtable = create_hashtable();
  hashtable->set(hashtable, "hello", "world");

  char *value = hashtable->get(hashtable, "hello");

  return (strcmp(value, "world") == 0);
}

int test_hashtable_set_overwrite() {
  struct HashTable *hashtable = create_hashtable();
  hashtable->set(hashtable, "hello", "world");
  hashtable->set(hashtable, "hello", "mars");

  char *value = hashtable->get(hashtable, "hello");

  return (strcmp(value, "mars") == 0);
}

int test_hashtable_not_set() {
  struct HashTable *hashtable = create_hashtable();
  hashtable->set(hashtable, "hello", "world");

  char *value = hashtable->get(hashtable, "foo");

  return (strcmp(value, "") == 0);
}

int test_hashtable_delete() {
  struct HashTable *hashtable = create_hashtable();
  hashtable->set(hashtable, "hello", "world");
  hashtable->delete(hashtable, "hello");

  char *value = hashtable->get(hashtable, "hello");

  return (strcmp(value, "") == 0);
}

int test_hashtable_contains() {
  struct HashTable *hashtable = create_hashtable();
  hashtable->set(hashtable, "hello", "world");

  int contains = hashtable->contains(hashtable, "hello");

  return (contains == 1);
}

int main() {
  struct TestRunner *test = describe("hashtable");
  test->it("should create a hashtable", &test_create_hashtable);
  test->it("should set and get an item of the hashtable", &test_hashtable_set_and_get);
  test->it("should set overwriting old item value in the hashtable", &test_hashtable_set_overwrite);
  test->it("should return empty string when key was not set", &test_hashtable_not_set);
  test->it("should delete an item of the hashtable", &test_hashtable_delete);
  test->it("should return 1 when hashtable contains an item", &test_hashtable_contains);
  test->end(test);
}
