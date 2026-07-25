# Two Sum (Sorted Array) — Approach

Use the **two pointers** technique: one pointer (`left`) starting at the beginning of the array and one pointer (`right`) starting at the end.

At each step, compute `nums[left] + nums[right]`:
- If it equals `target`, you found the answer.
- If it is less than `target`, move `left` forward (you need a bigger sum).
- If it is greater than `target`, move `right` backward (you need a smaller sum).

Because the array is sorted, this systematically narrows the search space without ever having to check every pair.

**Complexity:** O(n) time, O(1) extra space — instead of the O(n^2) brute force of checking every pair.
