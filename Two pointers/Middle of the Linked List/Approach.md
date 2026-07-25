# Middle of the Linked List — Approach

Use the **two pointers (slow/fast)** technique: move a slow pointer one step at a time and a fast pointer two steps at a time, both starting at `head`.

When the fast pointer reaches the end of the list (`fast == NULL` or `fast->next == NULL`), the slow pointer will be sitting at the middle node. Because the fast pointer moves twice as fast, by the time it has covered the whole list, the slow pointer has only covered half of it.

Walking through a list with an even number of nodes shows why this naturally lands on the *second* middle node — trace it by hand to convince yourself.

**Complexity:** O(n) time, O(1) extra space — no need to first count the length of the list.
