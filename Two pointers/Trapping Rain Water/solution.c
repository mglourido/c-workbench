
/*
esta funcion podría cachear los resultados de las operaciones ya hechas,
podría y debería añadir una comprobación de validez de maxLeft y maxRight
para ver si siguen siendo validos y así evitar tener que volver a obtenerlos
*/
int WaterTrapped(int *heights, int sizeHeights) {
  int solution = 0;

  for (int i = 0; i < sizeHeights; i++) {
    int pointerLeft = 0;
    int pointerRight = sizeHeights - 1;

    int maxLeft = 0;
    int maxRight = 0;

    while (pointerLeft < i || pointerRight > i) {
      if (pointerLeft < i) {
        if (maxLeft < heights[pointerLeft])
          maxLeft = heights[pointerLeft];
        pointerLeft++;
      }
      if (pointerRight > i) {
        if (maxRight < heights[pointerRight])
          maxRight = heights[pointerRight];
        pointerRight--;
      }
    }

    const int minMaxSize = maxLeft < maxRight ? maxLeft : maxRight;
    solution += minMaxSize - heights[i];
  }

  return solution;
}

// con comprobacion

int WaterTrappedLite(int *heights, int sizeHeights) {
  int solution = 0;

  int maxLeft = 0;
  int maxRight = 0;
  int indiceMaxLeft = -1;
  int indiceMaxRight = -1;

  for (int i = 0; i < sizeHeights; i++) {
    int pointerLeft = 0;
    int pointerRight = sizeHeights - 1;

    while ((pointerLeft < i || pointerRight > i) &&
           (indiceMaxLeft >= i || indiceMaxRight <= i)) {
      if (pointerLeft < i && indiceMaxLeft >= i) {
        if (maxLeft < heights[pointerLeft]) {
          maxLeft = heights[pointerLeft];
          indiceMaxLeft = pointerLeft;
        }
        pointerLeft++;
      }
      if (pointerRight > i && indiceMaxRight <= i) {
        if (maxRight < heights[pointerRight]) {
          maxRight = heights[pointerRight];
          indiceMaxRight = pointerRight;
        }
        pointerRight--;
      }
    }

    const int minMaxSize = maxLeft < maxRight ? maxLeft : maxRight;
    solution += minMaxSize - heights[i];
  }

  return solution;
}