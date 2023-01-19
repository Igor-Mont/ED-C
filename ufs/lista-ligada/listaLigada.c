#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *previous;
};

struct Node* createNode(int value, struct Node *previous) {
  struct Node *node = (struct Node*) malloc(sizeof(struct Node));
  node->value = value;

  if (!previous) {
    node->previous = NULL;
    return node;
  }

  node->previous = previous;
  return node;
}

int main() {
  struct Node *first = createNode(2020, NULL);
  struct Node *second = createNode(2021, first);
  struct Node *third = createNode(2022, second);

  struct Node *iterator = third;
  while (iterator) {
    printf("%d, ", iterator->value);
    iterator = iterator->previous;
  }

  return 0;
}