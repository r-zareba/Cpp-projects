
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

  char nazwa[20] = "Hello";
  const int max_n = 20;
  char napis[max_n];

  printf("nazwa: %s\n", nazwa);
  strcpy(nazwa, "Hellooo");
  printf("nazwa: %s", nazwa);

  printf("\nPodaj liczbe: ");
  fgets(napis, max_n, stdin);
  printf("n to: %s", napis);
  int x = atoi(napis);
  int y = x+5;

  return 0;
}
