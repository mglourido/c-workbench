# 3Sum

## Description

Given an integer array `nums`, return all the unique triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

The solution set must not contain duplicate triplets.

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
