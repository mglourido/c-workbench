# Reverse a String

## Description

Write a function that reverses a string. The input string is given as an array of characters, and it must be modified **in-place** with O(1) extra memory.

Use the **two pointers** technique: one pointer starting at the beginning of the array and one at the end. Swap the characters at both pointers, then move `left` forward and `right` backward, repeating until the pointers meet or cross.

## Input

- An array of characters `s`.

## Output

- The same array, modified in-place, with its characters in reverse order.

## Example

```
Input:  s = ['h', 'e', 'l', 'l', 'o']
Output: ['o', 'l', 'l', 'e', 'h']
```

```
Input:  s = ['H', 'a', 'n', 'n', 'a', 'h']
Output: ['h', 'a', 'n', 'n', 'a', 'H']
```

```
Input:  s = ['a']
Output: ['a']
```

## Constraints

- 1 <= s.length <= 10^5
- s[i] is a printable ASCII character
