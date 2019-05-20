#include <stdio.h>
#include <stdlib.h>

//deklaracja - prototyp
void funkcja1(int x, float *y);

int main(int argc, char const *argv[]) {

  int x = 10;
  float y = 0;

  printf("Number is %f", y);

  funkcja1(x, &y);
  printf("Number is %f", y);

  return 0;
}


//definicja
void funkcja1(int x, float *y){
  *y = x+5;
  return;
}
