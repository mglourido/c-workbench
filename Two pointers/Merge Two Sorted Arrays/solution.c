void mergeTwoSortedArrays(int *nums1, int *nums2, int m, int n) {
  int pointerArray1 = 0;
  int pointerArray2 = 0;

  int indiceJumps = 0;

  while (pointerArray1 < m + n) {

    const int numberSet = nums1[pointerArray1];
    while (nums2[pointerArray2] <= numberSet) {
      indiceJumps++;

      int temp = numberSet;
      int temp2 = 0;
      for (int i = pointerArray1 + 1; i < m + indiceJumps; i++) {
        temp2 = nums1[i];
        nums1[i] = temp;
        temp = temp2;
      }

      nums1[pointerArray1]=nums2[pointerArray2];
      
      pointerArray1++;
      pointerArray2++;
    }
    pointerArray1++;
  }
}