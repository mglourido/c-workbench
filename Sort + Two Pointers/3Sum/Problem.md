# 3Sum

## Description

Given an integer array `nums`, return all the unique triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

The solution set must not contain duplicate triplets.

This problem combines **sorting** with **two pointers**:

1. Sort the array first (O(n log n)).
2. Fix one element `nums[i]` and use two pointers (`left` starting right after `i`, `right` at the end of the array) to find pairs that sum with `nums[i]` to zero, moving the pointers inward based on the sum comparison.
3. Skip duplicate values for `i`, `left`, and `right` to avoid repeated triplets.

This reduces the brute-force O(n^3) approach to O(n^2).

## Input

- An array of integers `nums`.

## Output

- A list of unique triplets (each triplet as three integers) that sum to zero. Order of triplets and order of elements within a triplet does not matter, as long as there are no duplicate triplets.

## Example

```
Input:  nums = [-1, 0, 1, 2, -1, -4]
Output: [[-1, -1, 2], [-1, 0, 1]]
```

```
Input:  nums = [0, 1, 1]
Output: []
Explanation: No triplet sums to zero.
```

```
Input:  nums = [0, 0, 0]
Output: [[0, 0, 0]]
```

## Constraints

- 3 <= nums.length <= 3000
- -10^5 <= nums[i] <= 10^5
