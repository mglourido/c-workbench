int containerWithMostWaterFixed(int *heights, int sizeheights) {
  int pointerslow = 0;
  int pointerfast = sizeheights - 1;

  int maxContainer = -1;

  while (pointerslow < pointerfast) {
    const int ancho = pointerfast - pointerslow;
    int minheight = 0;

    if (heights[pointerslow] < heights[pointerfast]) {
      minheight = heights[pointerslow];
      pointerslow++;
    } else {
      minheight = heights[pointerfast];
      pointerfast--;
    }

    const int container = ancho * minheight;
    if (container > maxContainer)
      maxContainer = container;
  }
  return maxContainer;
}