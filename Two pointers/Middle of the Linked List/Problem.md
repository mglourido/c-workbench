# Middle of the Linked List

## Description

Given the head of a singly linked list, return the middle node of the linked list.

If there are two middle nodes (i.e., the list has an even number of nodes), return the **second** middle node.

Use the **two pointers (slow/fast)** technique: move a slow pointer one step at a time and a fast pointer two steps at a time, both starting at the head. When the fast pointer reaches the end of the list (or has no next node), the slow pointer will be at the middle.

This solves the problem in a single pass, O(n) time and O(1) extra space, without needing to first count the length of the list.

## Input

- The head of a singly linked list.

## Output

- A pointer to the middle node of the list.

## Example

```
Input:  list = [1, 2, 3, 4, 5]
Output: node with value 3
Explanation: The middle node of the list is the node with value 3.
```

```
Input:  list = [1, 2, 3, 4, 5, 6]
Output: node with value 4
Explanation: There are two middle nodes (value 3 and value 4);
since the list has an even number of elements, return the second one.
```

## Constraints

- The number of nodes in the list is in the range [1, 100]
- 1 <= Node.val <= 100
