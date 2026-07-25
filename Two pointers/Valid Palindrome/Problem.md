# Valid Palindrome

## Description

Given a string `s`, determine if it is a palindrome, considering only alphanumeric characters and ignoring case.

## Input

- A string `s`, which may contain letters, digits, spaces, and punctuation.

## Output

- `true` (1) if `s` is a palindrome under the given rules, `false` (0) otherwise.

## Example

```
Input:  s = "A man, a plan, a canal: Panama"
Output: true
Explanation: Ignoring non-alphanumeric characters and case, the string
reads "amanaplanacanalpanama", which is a palindrome.
```

```
Input:  s = "race a car"
Output: false
```

```
Input:  s = " "
Output: true
Explanation: After removing non-alphanumeric characters, the string is empty,
and an empty string is considered a valid palindrome.
```

## Constraints

- 1 <= s.length <= 2 * 10^5
- s consists only of printable ASCII characters
