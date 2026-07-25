# Longest Substring Without Repeating Characters — Approach

Use the **two pointers / sliding window** technique: a `left` pointer and a `right` pointer, both starting at the beginning of the string, defining a window `[left, right]` that always contains unique characters.

Expand the window by moving `right` forward, recording each new character in a tracking structure (e.g., a frequency or last-seen-index array of size 256 works well in C, since you're dealing with ASCII characters). If the character at `right` is already inside the current window, shrink the window by moving `left` forward (removing characters from the tracking structure as you go) until the duplicate is no longer inside the window.

Keep track of the maximum window size (`right - left + 1`) seen during the scan.

**Complexity:** O(n) time — each pointer moves forward at most n times, so the total work is linear even though it looks like a nested loop.
