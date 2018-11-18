#include <stdlib.h>
#include <stdio.h>

size_t maxSeq (int * array, size_t n) {
  if (array == NULL || n == 0)
    return 0;

  int curSeq = 1;
  int maxSeq = 1;
  for (int i = 1; i < n; i++) {
    if (array[i] > array [i-1])
      curSeq++;
    else 
      curSeq = 1;
    if (curSeq > maxSeq)
      maxSeq = curSeq;
  }
  return maxSeq;
}
