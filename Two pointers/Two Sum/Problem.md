# Two Sum (Sorted Array)

## Description

Given a sorted array of integers `nums` (ascending order) and an integer `target`, return the indices of the two numbers such that they add up to `target`.

You may assume that each input has **exactly one solution**, and you may not use the same element twice.

## Input

- An array of integers `nums`, sorted in non-decreasing order.
- An integer `target`.

## Output

- Two indices (0-based) `i` and `j` such that `nums[i] + nums[j] == target`.

## Example

```
Input:  nums = [2, 7, 11, 15], target = 9
Output: [0, 1]
Explanation: nums[0] + nums[1] = 2 + 7 = 9
```

```
Input:  nums = [1, 3, 4, 6, 10, 15], target = 16
Output: [3, 4]
Explanation: nums[3] + nums[4] = 6 + 10 = 16
```

## Constraints

- 2 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9
- nums is sorted in ascending order
- Exactly one valid solution exists
