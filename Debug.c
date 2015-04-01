
#include <stdio.h>
#include "MatLib.h"

int main() {
  printf("Debug\n");
  matrix* A = mat_init(2,2);
  mat_print(A);
  return 0;
}
