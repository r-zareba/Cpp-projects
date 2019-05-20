
#include <stdio.h>
#include "my_header.h"

int main(int argc, char const *argv[]) {

  int x = 5;
  int *wsk = &x;

  printf("Number is %d", *wsk);

  return 0;
}
