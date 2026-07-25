# Valid Palindrome — Approach

Use the **two pointers** technique: one pointer (`left`) starting at the beginning of the string and one pointer (`right`) starting at the end, moving toward the center.

At each step:
- If `s[left]` is not alphanumeric, advance `left` (skip it).
- If `s[right]` is not alphanumeric, move `right` backward (skip it).
- Otherwise, compare `s[left]` and `s[right]` case-insensitively. If they differ, it's not a palindrome. If they match, advance `left` and move `right` backward.

Stop when `left >= right`. If no mismatch was found, the string is a palindrome under the given rules.

**Complexity:** O(n) time, O(1) extra space.
