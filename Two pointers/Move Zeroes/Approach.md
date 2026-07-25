# Move Zeroes — Approach

Use the **two pointers** technique: a slow pointer (`insertPos`) marking where the next non-zero element should go, and a fast pointer scanning through the array.

Whenever the fast pointer finds a non-zero value, place it at `nums[insertPos]` and advance `insertPos`. After the fast pointer finishes scanning the whole array, every position from `insertPos` to the end is filled with `0`.

**Complexity:** O(n) time, O(1) extra space, and a single pass over the array.
