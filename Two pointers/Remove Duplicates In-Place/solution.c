int removeDuplicates(int *nums, int sizeNums) {
  if (sizeNums == 0)
    return 0;

  int slow = 0;

  for (int fast = 1; fast < sizeNums; fast++) {
    if (nums[fast] != nums[slow])
      nums[++slow] = nums[fast];
  }

  return slow + 1;
}