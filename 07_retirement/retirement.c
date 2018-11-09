#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double compute_savings(double balance, retire_info data) {
  return data.contribution + balance * data.rate_of_return;
}

void print_balance(int age, double balance) {
    printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, balance);
}

void retirement (int startAge, double initial, retire_info working, retire_info retired) {

  double balance = initial;
  int age = startAge;

  // working time
  for (int i = 0; i < working.months; i++) {
    print_balance(age, balance);

    // compute new account balance every month
    balance += compute_savings(balance, working);
    age++;
  }

  // retirement
  for (int i = 0; i < retired.months; i++) {
    print_balance(age, balance);

    balance += compute_savings(balance, retired);
    age++;
  }
}

int main (void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired = { .months = 384, .contribution = -4000.0, .rate_of_return = 0.01 / 12};

  int age = 327;
  double savings = 21345.0;

  retirement(age, savings, working, retired);

  return EXIT_SUCCESS;
}
