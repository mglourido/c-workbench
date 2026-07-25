# 3Sum — Approach

This problem combines **sorting** with **two pointers**:

1. Sort the array first (O(n log n)). This makes duplicates adjacent and enables the two-pointer scan below.
2. Iterate with an index `i` over the sorted array (this is just a regular loop, not a moving "pointer" in the two-pointer sense). For each `i`, you need two other numbers, `nums[left]` and `nums[right]`, such that `nums[i] + nums[left] + nums[right] == 0` — i.e. `nums[left] + nums[right] == -nums[i]`.
3. Within that fixed `i`, run a **two pointers** scan: `left = i + 1`, `right = nums.length - 1`. Compare `nums[left] + nums[right]` against `-nums[i]` and move `left` forward or `right` backward accordingly, just like in Two Sum on a sorted array.
4. To avoid duplicate triplets: skip over repeated values for `i` (if `nums[i] == nums[i-1]`, skip), and after finding a valid triplet, skip over repeated values for both `left` and `right` before continuing.

**Complexity:** O(n^2) time (O(n log n) sort + O(n) two-pointer scan per `i`), O(1) extra space (aside from the output and the sort) — much better than the brute-force O(n^3) of checking every triplet.
