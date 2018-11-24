#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

int main (void) {
  if (power(3, 3) != 27)
    exit(EXIT_FAILURE);
  if (power(1, 4) != 1)
    exit(EXIT_FAILURE);
  if (power(-3, 5) != -243)
    exit(EXIT_FAILURE);    
  if (power(0, 0) != 1)
    exit(EXIT_FAILURE);
  
  return EXIT_SUCCESS;
}
