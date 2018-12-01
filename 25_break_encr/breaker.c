#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void countFrequency(FILE * f, int * array) {
  int c = 0;
  int checkEmptyFile = 0;
  while ((c = fgetc(f)) != EOF) {
    checkEmptyFile++;
    if (isalpha(c)) {
      c = tolower(c);
      array[c-97]++;
    }
  }
  if (checkEmptyFile == 0) {
    fprintf(stderr, "Empty file!\n");
    exit(EXIT_FAILURE);
  }
}

int getMax(int array[]) {
  int i = 1;
  int index = 0;
  int maxLett = 0;
  while (i < 26){
    if (array[i] > maxLett) {
      maxLett = array[i];
      index = i;
    }
    i++;
  }
  return index;
}

int decrypt(FILE * f) {
  int array[26] = {0};
  countFrequency(f, array);

  int pos_e = getMax(array);
  int code = pos_e + 97 - 'e';  

  return code;
}

int main(int argc, char ** argv) { 
  int code = 0;
  if (argc != 2) {    
    fprintf(stderr,"Usage: decrypt inputFileName\n");    
    return EXIT_FAILURE;  
  }  
  FILE * f = fopen(argv[1], "r");  
  if (f == NULL) {    
    perror("Could not open file");    
    return EXIT_FAILURE;  
  }

  code = decrypt(f);
  printf("%d\n", code);

  if (fclose(f) != 0) {    
    perror("Failed to close the input file!");    
    return EXIT_FAILURE;  
  }
  return EXIT_SUCCESS;  
}
