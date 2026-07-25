# Reverse a String — Approach

Use the **two pointers** technique: one pointer at the beginning of the array and one at the end.

Swap the characters at both pointers, then move `left` forward and `right` backward, repeating until the pointers meet or cross (`left >= right`).

**Complexity:** O(n) time, O(1) extra space.
