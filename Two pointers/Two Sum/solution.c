#include <stdlib.h> //library for using malloc()

int *TwoSum(int *nums, int numsSize, int target) {
  const int nSolutions = 2;
  int *solutionReturn = malloc(sizeof(int) * nSolutions);

  int pointerLeft = 0;
  int pointerRight = numsSize - 1;
  int sum = nums[pointerLeft] + nums[pointerRight];

  while (sum != target) {
    if (sum > target) {
      pointerRight -= 1;
    } else if (sum < target) {
      pointerLeft += 1;
    } else
      break;

    sum = nums[pointerLeft] + nums[pointerRight];
  }

  solutionReturn[0] = pointerLeft;
  solutionReturn[1] = pointerRight;

  return solutionReturn;
}

/*Como se aseguro que hay una solucion no hay que poner prevecion de que Ambos
pointers apuntan al mismo indice o de bucle infinito o error de indice que no
existe en el array*/

// Si puede que no tenga solucion
#include <stdbool.h>
int *TwoSumWithoutSolution(int *nums, int numsSize, int target) {
  const int nSolutions = 2;
  int *solutionReturn = malloc(sizeof(int) * nSolutions);

  int pointerLeft = 0;
  int pointerRight = numsSize - 1;
  int sum = nums[pointerLeft] + nums[pointerRight];

  bool Withsolution = false;

  while (sum != target) {
    if (sum > target) {
      pointerRight -= 1;
    } else if (sum < target) {
      pointerLeft += 1;
    } else
      break;

    if (pointerLeft >= pointerRight) {
      Withsolution = false;
      break;
    }

    sum = nums[pointerLeft] + nums[pointerRight];
  }

  if (!Withsolution) {
    free(solutionReturn); // prevents memory leak
    return NULL;
  }

  solutionReturn[0] = pointerLeft;
  solutionReturn[1] = pointerRight;

  return solutionReturn;
}