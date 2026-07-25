# Remove Duplicates In-Place — Approach

Use the **two pointers** technique: a slow pointer marking the position of the last unique element written, and a fast pointer scanning ahead through the array.

The fast pointer visits every element. Whenever `nums[fast] != nums[slow]`, it means a new unique value was found: advance `slow` and copy `nums[fast]` into `nums[slow]`. Because the array is sorted, all duplicates of a value are adjacent, so comparing only against the last written unique value is enough to detect them.

At the end, `slow + 1` is the count of unique elements `k`.

**Complexity:** O(n) time, O(1) extra space.
