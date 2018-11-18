#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

size_t maxSeq (int * array, size_t n);

int main (void) {

  int array0[] = {};
  int array1[] = {2, 4, UINT_MAX};
  int array2[] = {0, 2, 2, 4, 4};
  int array3[] = {1, 0, 2, 1, 4};
  int array4[] = {0, 23, 2, -3, 4, 16, 16, 82, 99};

  if (maxSeq(array0, 0) != 0) {
    printf("Failed on 0\n");
    return EXIT_FAILURE;
  }
  
  if (maxSeq(array1, 4) != 2) {
    printf("Failed on 1\n");
    return EXIT_FAILURE;
  }
  
  if (maxSeq(array2, 5) != 2) {
    printf("Failed on 2\n");
    return EXIT_FAILURE;
  }

  if (maxSeq(array3, 5) != 2) {
    printf("Failed on 3\n");
    return EXIT_FAILURE;
  }
  
  if (maxSeq(array4, 9) != 3) {
    printf("Failed on 4\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
