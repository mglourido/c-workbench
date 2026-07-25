#include <stdbool.h>

// functions to improve readability
bool IsLetter(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void MoveNextLetter(int s, int *pointer, int limit, bool left) {
  pointer += left ? -1 : +1;
  while (!IsLetter(s[pointer]) &&
         ((left && (*pointer > limit)) || (!left && (*pointer < limit)))) {
    pointer += left ? -1 : +1;
  }
}

bool ValidPalindrime(char *s) {
  bool isPalindrome = true;

  int pointerLeft = 0;
  int pointerRight = 0;

  while (pointerLeft < pointerRight) {
    const char caracterLeft = s[pointerLeft];
    const char caracterRight = s[pointerRight];

    if (caracterLeft == caracterRight) {
      // move pointerLeft to the next letter
      MoveNextLetter(*s, &pointerLeft, pointerRight, false);

      // move pointerRight to the next letter
      MoveNextLetter(*s, &pointerRight, pointerLeft, true);
    } else if (caracterLeft != caracterRight) {
      if (!IsLetter(caracterLeft)) {
        // move pointerLeft to the next letter
        MoveNextLetter(*s, &pointerLeft, pointerRight, false);
      }
      if (!IsLetter(caracterRight)) {
        // move pointerRight to the next letter
        MoveNextLetter(*s, &pointerRight, pointerLeft, true);
      }
    } else {
      isPalindrome = false;
      break;
    }
  }

  return isPalindrome;
}