int removeDuplicates(int *nums, int sizeNums) {
  int k = sizeNums-1;

  int pointerSet = 0; // pointer that sets the number being checked
  int pointerSearch = 0;

  while (pointerSet < k) {
    const int numRevise = nums[pointerSet];
    pointerSearch = pointerSet+1;

    while (nums[pointerSearch] == numRevise)
      pointerSearch++;

    int steps = pointerSearch - pointerSet;
    k -= steps;

    // reposition elements
    while (pointerSearch < k) {
      steps++;
      pointerSearch++;
      nums[pointerSearch - steps] = nums[pointerSearch];
    }

    pointerSet++;
  }

  return k;
}