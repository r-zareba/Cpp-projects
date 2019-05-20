
#include <stdio.h>
#include <stdlib.h>

// definicja naszego typu
typedef struct Node {
  int data;
  struct Node *next;
} Node;


void insert(Node **ptr_head, int x);
void print(Node *head);


int main(int argc, char const *argv[]) {

  int n, i, x;

  // stworzenie pierwszego elementu listy i wypełnienie zerami
  Node *head = NULL;

  printf("How long the list should be?\n");
  scanf("%d", &n);

  for (i=0; i<n; i++){
    printf("Enter the number: ");
    scanf("%d", &x);

    // Przekazanie wskaznika do wskaznika ktory wskazuje na pierwszy element listy
    insert(&head, x);
    print(head);
  }


  return 0;
}

void insert(Node **ptr_head, int x){

  // stworzenie dynamicznie miejsca w pamięci dla nowego elementu listy
  Node *temp = (Node*) malloc(sizeof(struct Node));

  // wypelnienie struktury danymi
  temp->data = x;

  // ustawienie wskaznika na NULL - ustawiamy element jako ostatni
  temp->next = NULL;

  // Jesli head nie jest NULL, czyli jesli jest juz jakis element w liscie
  if (*ptr_head != NULL) temp->next = *ptr_head;
  *ptr_head = temp;
}

void print(Node *head){
  printf("List is: ");
  while (head != NULL){
    printf("%d , ", head->data);
    head = head->next;
  }
  printf("\n");
}
