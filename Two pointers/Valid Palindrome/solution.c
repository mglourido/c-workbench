#include <stdbool.h>

// functions to improve readability
bool IsLetter(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
bool IsNumber(char c) { return (c >= '0' && c <= '9'); }

void MoveNextLetter(char *s, int *pointer, int limit, bool left) {
  *pointer += left ? -1 : +1;
  while ((!IsLetter(s[*pointer]) && !IsNumber(s[*pointer])) &&
         ((left && (*pointer > limit)) || (!left && (*pointer < limit)))) {
    *pointer += left ? -1 : +1;
  }
}

bool compare(char c1, char c2) {
  if (c1 == c2)
    return true;

  if (IsLetter(c1) && IsLetter(c2)) {
    if (c1 + 32 == c2 || c1 - 32 == c2)
      return true;
  }

  return false;
}

bool ValidPalindrime(char *s, int sizeS) {
  bool isPalindrome = true;

  int pointerLeft = 0;
  int pointerRight = sizeS - 1;

  while (pointerLeft < pointerRight) {
    const char caracterLeft = s[pointerLeft];
    const char caracterRight = s[pointerRight];

    if (compare(caracterLeft, caracterRight)) {
      // move pointerLeft to the next letter
      MoveNextLetter(s, &pointerLeft, pointerRight, false);

      // move pointerRight to the next letter
      MoveNextLetter(s, &pointerRight, pointerLeft, true);
    } else {
      if ((IsLetter(caracterLeft) || IsNumber(caracterLeft)) &&
          (IsLetter(caracterRight) || IsNumber(caracterRight))) {
        isPalindrome = false;
        break;
      }
      if (!IsLetter(caracterLeft) && !IsNumber(caracterLeft)) {
        // move pointerLeft to the next letter
        MoveNextLetter(s, &pointerLeft, pointerRight, false);
      }
      if (!IsLetter(caracterRight) && !IsNumber(caracterRight)) {
        // move pointerRight to the next letter
        MoveNextLetter(s, &pointerRight, pointerLeft, true);
      }
    }
  }

  return isPalindrome;
}