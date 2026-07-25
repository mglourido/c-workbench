# Container With Most Water

## Description

You are given an array of integers `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i`-th line are `(i, 0)` and `(i, height[i])`.

Find two lines that, together with the x-axis, form a container that holds the most water.

Return the maximum amount of water the container can store.

Use the **two pointers** technique: start with one pointer at the beginning and one at the end of the array. At each step, compute the area formed by the two pointers, keep track of the maximum, and move the pointer pointing to the shorter line inward (since moving the taller one can never increase the area).

## Input

- An array of non-negative integers `height`.

## Output

- A single integer: the maximum area of water that can be contained.

## Example

```
Input:  height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
Output: 49
Explanation: The lines at index 1 (height 8) and index 8 (height 7)
form a container of width 7 and height min(8,7) = 7, giving area 49.
```

```
Input:  height = [1, 1]
Output: 1
```

## Constraints

- 2 <= height.length <= 10^5
- 0 <= height[i] <= 10^4
