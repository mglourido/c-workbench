# Merge Two Sorted Arrays — Approach

Use the **two pointers** technique, but working **from the end** of both arrays instead of the start.

Set up three pointers:
- `i = m - 1` (last valid element of `nums1`)
- `j = n - 1` (last element of `nums2`)
- `k = m + n - 1` (last position of the combined array)

While `j >= 0`: compare `nums1[i]` and `nums2[j]`, place the larger one at `nums1[k]`, then move `k` and the pointer of whichever value was placed backward. If `i` becomes negative, just copy the rest of `nums2` directly.

Working from the end avoids overwriting values in `nums1` that haven't been read yet — merging from the front would require shifting elements, which is what filling from the back avoids.

**Complexity:** O(m + n) time, O(1) extra space.
