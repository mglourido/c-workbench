#include <stdlib.h>

typedef int item;
typedef struct node *tPos;

struct node {
  item Item;
  tPos next;
};

typedef tPos *tList;

tPos middleNode(tList nums) {
  if (nums == NULL)
    return NULL;

  tPos pointerMiddle = *nums; // slow
  tPos pointerEnd = *nums;    // fast

  while (pointerEnd != NULL && pointerEnd->next != NULL) {
    pointerEnd = pointerEnd->next->next;
    pointerMiddle = pointerMiddle->next;
  }

  return pointerMiddle;
}