
#include <stdio.h>
#include <stdlib.h>


void printAttributes(struct *st, char *attributes);

struct Dog{
  char name[50];
  char color[20];
  int age;

};

int main(int argc, char const *argv[]) {

  struct Dog baster = {
    "Blofster",
    "brazowy",
    16
  };

  // wskaznik do struktury
  struct Dog *wsk = &baster;



  printf("%d", baster.age);
  printf("\n%d", wsk -> age);


  return 0;
}

void printAttributes(struct *st, char *attributes){

  for (int *i=st; *i; i++){
    printf(i)
  }
}
