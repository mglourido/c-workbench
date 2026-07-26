
int containerWithMostWater(int *heights, int sizeheights) {
  int pointerslow = 0;
  int pointerfast = 0;

  int maxContainer = -1;

  while (pointerfast <= sizeheights) {
    const int heightmin = heights[pointerslow] < heights[pointerfast]
                        ? heights[pointerslow]
                        : heights[pointerfast];

    const int container = heightmin * (pointerslow + 1);

    if (maxContainer < container) {
      maxContainer = container;
    }

    pointerslow += 1;
    pointerfast += 2;
  }

  return maxContainer;
}