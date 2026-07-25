# Linked List Cycle Detection

## Description

Given the head of a singly linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if some node in the list can be reached again by continuously following the `next` pointer.

## Input

- The head of a singly linked list. Nodes have an integer `val` and a `next` pointer.
- Note: to build the test case, you may represent the cycle by giving the position (0-based index) where the tail connects back to, or `-1` if there is no cycle. This is only for constructing the test input; your function should only receive the `head` pointer.

## Output

- `true` (1) if the linked list has a cycle, `false` (0) otherwise.

## Example

```
Input:  values = [3, 2, 0, -4], pos = 1
List:   3 -> 2 -> 0 -> -4 -> (back to node at index 1, value 2)
Output: true
```

```
Input:  values = [1, 2], pos = -1
List:   1 -> 2 -> NULL
Output: false
```

```
Input:  values = [1], pos = -1
List:   1 -> NULL
Output: false
```

## Constraints

- The number of nodes in the list is in the range [0, 10^4]
- -10^5 <= Node.val <= 10^5
- pos is -1 or a valid index in the linked list
