# Merge Two Sorted Arrays

## Description

You are given two integer arrays `nums1` and `nums2`, sorted in non-decreasing order, and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.

`nums1` has a total length of `m + n`, where the first `m` elements are the actual values and the last `n` elements are set to `0` and should be ignored — this extra space is reserved to hold the merged result.

Merge `nums2` into `nums1` **in-place** so that `nums1` becomes a single sorted array of length `m + n`.

## Input

- Array `nums1` of length `m + n` (first `m` values valid, rest are placeholders).
- Integer `m`: number of valid elements in `nums1`.
- Array `nums2` of length `n`.
- Integer `n`: number of elements in `nums2`.

## Output

- `nums1` modified in-place to contain all `m + n` elements merged in sorted order.

## Example

```
Input:  nums1 = [1, 2, 3, 0, 0, 0], m = 3, nums2 = [2, 5, 6], n = 3
Output: nums1 = [1, 2, 2, 3, 5, 6]
```

```
Input:  nums1 = [1], m = 1, nums2 = [], n = 0
Output: nums1 = [1]
```

```
Input:  nums1 = [0], m = 0, nums2 = [1], n = 1
Output: nums1 = [1]
```

## Constraints

- nums1.length == m + n
- nums2.length == n
- 0 <= m, n <= 200
- 1 <= m + n <= 200
- -10^9 <= nums1[i], nums2[j] <= 10^9
