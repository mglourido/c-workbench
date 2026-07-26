#include <stdbool.h>
#include <stdlib.h>

typedef struct node *head;
struct node {
  int val;
  head next;
};

bool cycle(head *l) {
  if (l == NULL)
    return false;

  bool solution = false;

  head pointerleft = *l;
  head pointerRight = pointerleft;

  while (pointerleft != NULL) {
    pointerRight = pointerleft;
    while (pointerRight != NULL) {
      pointerRight = pointerRight->next;
      if (pointerRight->val == pointerleft->val) {
        solution = true;
        break;
      }
    }
  }

  return solution;
}