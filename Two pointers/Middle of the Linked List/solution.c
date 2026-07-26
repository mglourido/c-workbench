#include <stdlib.h>

typedef int item;
typedef struct node *tPos;

struct node {
  item Item;
  tPos next;
};

typedef tPos *tList;

int middleNode(tList nums) {
  if (nums == NULL)
    return NULL;

  if ((*nums)->next == NULL) {
    return (*nums)->Item;
  }

  tPos pointerMiddle = *nums; // slow
  tPos pointerEnd = *nums;    // fast

  while (pointerEnd->next->next != NULL) {
    pointerEnd = pointerEnd->next->next;
    pointerMiddle = pointerMiddle->next;
  }

  //If there are two options, take the one on the right.
  if (pointerEnd->next == NULL)
    pointerMiddle = pointerMiddle->next;

  return pointerMiddle->Item;
}