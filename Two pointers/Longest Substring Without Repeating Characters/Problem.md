# Longest Substring Without Repeating Characters

## Description

Given a string `s`, find the length of the longest substring without repeating characters.

Use the **two pointers / sliding window** technique: a `left` pointer and a `right` pointer both starting at the beginning of the string, defining a window `[left, right]` that always contains unique characters.

Expand the window by moving `right` forward, adding each new character to a tracking structure (e.g., a set or a frequency/last-seen-index array, since we're in C). If the character at `right` is already inside the window, shrink the window by moving `left` forward (removing characters from the tracking structure) until the duplicate is gone. Keep track of the maximum window size seen.

This solves the problem in O(n) time, since each pointer moves forward at most n times.

## Input

- A string `s` (may contain letters, digits, symbols, and spaces).

## Output

- A single integer: the length of the longest substring without repeating characters.

## Example

```
Input:  s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with a length of 3.
```

```
Input:  s = "bbbbb"
Output: 1
Explanation: The answer is "b", with a length of 1.
```

```
Input:  s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with a length of 3.
Note that "pwke" is a subsequence, not a substring.
```

## Constraints

- 0 <= s.length <= 5 * 10^4
- s consists of printable ASCII characters
