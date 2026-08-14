int WaterTrapped(int *heights, int sizeHeights) {
  int solution = 0;

  int pointerLeft = 0;
  int pointerRight = sizeHeights - 1;
  int maxLeft = 0;
  int maxRight = 0;

  while (pointerLeft < pointerRight) {
    if (heights[pointerLeft] < heights[pointerRight]) {
      if (maxLeft < heights[pointerLeft])
        maxLeft = heights[pointerLeft];
      solution += maxLeft - heights[pointerLeft];
      pointerLeft++;
    } else {
      if (maxRight < heights[pointerRight])
        maxRight = heights[pointerRight];
      solution += maxRight - heights[pointerRight];
      pointerRight--;
    }
  }

  return solution;
}