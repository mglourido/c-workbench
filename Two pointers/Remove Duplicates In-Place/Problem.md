# Remove Duplicates In-Place

## Description

Given a sorted array of integers `nums`, remove the duplicates **in-place** such that each unique element appears only once. The relative order of the elements should be kept the same.

Since you cannot change the length of the array in some languages, instead modify the array so that the first `k` elements contain the unique elements (in order), and return `k`, the number of unique elements. It does not matter what values are left beyond the first `k` elements.

## Input

- An array of integers `nums`, sorted in non-decreasing order.

## Output

- An integer `k`: the number of unique elements.
- The first `k` positions of `nums` must contain the unique elements in order.

## Example

```
Input:  nums = [1, 1, 2, 2, 3, 4, 4, 4, 5]
Output: k = 5, nums = [1, 2, 3, 4, 5, ...]
```

```
Input:  nums = [0, 0, 0, 1, 1, 2]
Output: k = 3, nums = [0, 1, 2, ...]
```

## Constraints

- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- nums is sorted in non-decreasing order
