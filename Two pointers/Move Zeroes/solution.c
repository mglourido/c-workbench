void moveZeroes(int *nums, int sizeNums) {
  int insertPos = 0;

  for (int i = 0; i < sizeNums; i++) {
    if (nums[i] != 0) {
      const int temp = nums[insertPos];
      nums[insertPos] = nums[i];
      nums[i] = temp;
      insertPos++;
    }
  }
}
