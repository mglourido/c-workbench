# Sort Colors (Dutch National Flag)

## Description

Given an array `nums` with `n` elements, where each element is either `0`, `1`, or `2`, sort the array **in-place** so that elements of the same value are grouped together, in the order `0`, `1`, `2` — without using a library sort function.

## Input

- An array of integers `nums`, where each value is `0`, `1`, or `2`.

## Output

- The same array, sorted in-place so all `0`s come first, then all `1`s, then all `2`s.

## Example

```
Input:  nums = [2, 0, 2, 1, 1, 0]
Output: [0, 0, 1, 1, 2, 2]
```

```
Input:  nums = [2, 0, 1]
Output: [0, 1, 2]
```

```
Input:  nums = [0]
Output: [0]
```

## Constraints

- 1 <= nums.length <= 300
- nums[i] is 0, 1, or 2
