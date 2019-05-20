#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]) {

  int n;
  printf("Enter size of array: ");
  scanf("%d", &n );

  //dynamiczne stworzenie listy wskaznikow typu int
  // int *a = (int*) malloc(n*sizeof(int));

  // calloc inicjuje wartosci zerami
  int *a = (int*) calloc(n, sizeof(int));

  // nadanie wartosci
  // for (int i=0; i<n; i++){
  //   a[i] = i+1;
  // }

  // wyswietlanie elementow tablicy
  for (int i=0; i<n; i++){
    printf("%d ", a[i]);
  }

  free(a);


  return 0;
}
