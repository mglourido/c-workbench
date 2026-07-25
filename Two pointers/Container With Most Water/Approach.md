# Container With Most Water — Approach

Use the **two pointers** technique: start with one pointer at the beginning and one at the end of the array.

At each step, compute the area formed by the two pointers (`width * min(height[left], height[right])`), keep track of the maximum seen so far, and move the pointer pointing to the **shorter** line inward.

Why move the shorter one? The width always shrinks as pointers move inward, so the only way to potentially get a larger area is to increase the limiting height. Moving the taller line inward can never help (the limiting height stays the same or gets worse), so it's always safe — and necessary — to move the shorter one.

**Complexity:** O(n) time, O(1) extra space — instead of the O(n^2) brute force of checking every pair of lines.
