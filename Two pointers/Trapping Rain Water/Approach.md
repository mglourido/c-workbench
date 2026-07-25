# Trapping Rain Water — Approach

Use the **two pointers** technique: a `left` pointer starting at the beginning and a `right` pointer starting at the end. Keep track of `left_max` and `right_max`, the highest bar seen so far from each side.

At each step, compare `left_max` and `right_max`:
- Move the pointer on the side with the **smaller** max height inward.
- The water trapped above that bar is `side_max - height[pointer]` (never negative, because the other side is guaranteed to be at least as tall — that's the invariant that makes this correct).
- Add this amount to the running total, update the corresponding max, and advance the pointer.

**Complexity:** O(n) time, O(1) extra space — instead of precomputing left-max/right-max arrays (O(n) space) or a brute-force O(n^2) scan per bar.
