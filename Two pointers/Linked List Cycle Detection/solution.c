#include <stdbool.h>
#include <stdlib.h>

typedef struct node *Node;
struct node {
  int val;
  Node next;
};

bool cycle(Node *l) {
  if (l == NULL)
    return false;

  Node slow = *l;
  Node fast = *l;

  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast)
      return true;
  }

  return false;
}
