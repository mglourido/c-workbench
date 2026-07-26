void moveZeroes(int *nums, int sizeNums) {
  const int k = sizeNums - 1;

  int pointerSet = 0;

  int zerosTotal = 0;
  int zerosMoved = 0;

  // count zeros
  for (int i = 0; i < sizeNums; i++) {
    if (nums[i] == 0)
      zerosTotal++;
  }

  // move zeros
  while (zerosMoved < zerosTotal) {
    if (nums[pointerSet] == 0) {
      int pointerSwap = pointerSet;
      int zerosDetected = 0;
      while (pointerSwap < k - zerosMoved) {

        if (nums[pointerSwap] == 0)
          zerosDetected++;
        // This stops the loop when it reaches the end, preventing it from
        // moving zeros that are already at the end. This is useful because if
        // there are zeros at the end of the array that aren't yet being moved,
        // they aren't counted and are considered non-zero numbers, thus
        // reducing the number of loop iterations.
        if (k - pointerSwap <= zerosTotal - zerosDetected - zerosMoved)
          break;

        const int temp = nums[pointerSwap];
        const int indiceSwap = pointerSwap + 1;

        nums[pointerSwap] = nums[indiceSwap];
        nums[indiceSwap] = temp;

        pointerSwap++;
      }
      zerosMoved++;
    }

    pointerSet++;
  }
}