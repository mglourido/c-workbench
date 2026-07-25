# Linked List Cycle Detection — Approach

Use the **two pointers (slow/fast)** technique, also known as **Floyd's Cycle Detection Algorithm**.

Move a slow pointer one step at a time (`slow = slow->next`) and a fast pointer two steps at a time (`fast = fast->next->next`), both starting at `head`.

- If there is no cycle, the fast pointer will reach the end of the list (`NULL`) first.
- If there is a cycle, the fast pointer will eventually "lap" the slow pointer and they will point to the same node.

Remember to guard against `fast` or `fast->next` being `NULL` before dereferencing, to avoid crashing when there's no cycle.

**Complexity:** O(n) time, O(1) extra space — no need for a hash set to track visited nodes.
