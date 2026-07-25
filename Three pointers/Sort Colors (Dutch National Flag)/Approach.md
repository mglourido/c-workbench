# Sort Colors (Dutch National Flag) — Approach

This is the classic **Dutch National Flag** problem, solved with **three pointers** that all move within a single pass:

- `low`: boundary for the next position where a `0` should go.
- `mid`: the current element being examined.
- `high`: boundary for the next position (from the end) where a `2` should go.

Iterate with `mid` starting at the beginning of the array, while `mid <= high`:

- If `nums[mid] == 0`: swap `nums[mid]` and `nums[low]`, then advance both `low` and `mid`.
- If `nums[mid] == 1`: it's already in the right region, just advance `mid`.
- If `nums[mid] == 2`: swap `nums[mid]` and `nums[high]`, then decrement `high` — but do **not** advance `mid`, because the value swapped in from `high` still needs to be examined.

By the time `mid` passes `high`, everything before `low` is `0`, everything between `low` and `mid` is `1`, and everything after `high` is `2`.

**Complexity:** O(n) time, O(1) extra space, single pass — instead of sorting (O(n log n)) or counting values and doing two passes.
