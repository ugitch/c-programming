void rotate(char matrix[10][10]) {
  int n = 9;
  char matrix_copy[10][10] = {0};
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      matrix_copy[i][j] = matrix[i][j];      
    }
  }

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      matrix[i][j] = matrix_copy[n-j][i];
    }
  }
}

