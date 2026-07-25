# Move Zeroes

## Description

Given an integer array `nums`, move all `0`s to the end of it while maintaining the relative order of the non-zero elements.

This must be done **in-place** without making a copy of the array.

## Input

- An array of integers `nums`.

## Output

- The same array, modified in-place: non-zero elements in their original relative order, followed by all the zeroes.

## Example

```
Input:  nums = [0, 1, 0, 3, 12]
Output: [1, 3, 12, 0, 0]
```

```
Input:  nums = [0]
Output: [0]
```

```
Input:  nums = [1, 0, 2, 0, 0, 3]
Output: [1, 2, 3, 0, 0, 0]
```

## Constraints

- 1 <= nums.length <= 10^4
- -2^31 <= nums[i] <= 2^31 - 1
