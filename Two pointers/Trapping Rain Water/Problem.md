# Trapping Rain Water

## Description

Given `n` non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Use the **two pointers** technique: a `left` pointer starting at the beginning and a `right` pointer starting at the end. Keep track of `left_max` and `right_max`, the highest bar seen so far from each side.

At each step, move the pointer on the side with the smaller max height inward: the water trapped above that bar is `side_max - height[pointer]` (which is never negative, because the other side is guaranteed to be at least as tall). Add this to the total and advance the pointer.

This solves the problem in O(n) time and O(1) extra space.

## Input

- An array of non-negative integers `height`.

## Output

- A single integer: the total units of water trapped.

## Example

```
Input:  height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
Output: 6
```

```
Input:  height = [4, 2, 0, 3, 2, 5]
Output: 9
```

```
Input:  height = [1, 1, 1]
Output: 0
```

## Constraints

- 1 <= height.length <= 2 * 10^4
- 0 <= height[i] <= 10^5
