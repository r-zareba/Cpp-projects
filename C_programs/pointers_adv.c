#include <stdio.h>
#include <stdlib.h>

void funkcja(char **ptr_x);

int main(int argc, char const *argv[]) {


  char *ptr_x[] = {"Tekst1", "Tekst2", "Tekst3", ""};
  int i;
  char **cpp;

  funkcja(ptr_x);
  funkcja(ptr_x);
  funkcja(ptr_x);

  // printf("%s\n", ptr_x[0]);

  // for (i=0; *ptr_x[i]; i++){
  //   printf("%s\n", ptr_x[i]);
  // }
  //
  // for (cpp=ptr_x; **cpp; cpp++){
  //   printf("%s\n", *cpp);
  // }

  return 0;
}

void funkcja(char **ptr_x){
  for (int i=0; *ptr_x[i]; i++){
    printf("%s\n", ptr_x[i]);
  }

  return;
}
