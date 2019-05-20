#include <stdio.h>
#include <stdlib.h>


typedef struct Settings{
  int power;
} Settings;

typedef struct SettingsList{
  Settings *settings_ptr;
  struct SettingsList *next;
} SettingsList;

SettingsList *head; //pierwszy element listy
struct Settings *create_new_setting(const int power);
void free_setting(Settings *setting);
void insert_setting(Settings *setting, int index);
void remove_setting(int index);
Settings *get_setting(int index);
void print_all_settings();



int main(int argc, char const *argv[]) {

  // inicjalizacja pierwszego elementu listy
  head = NULL;

  Settings *my_setting1 = create_new_setting(5);
  Settings *my_setting2 = create_new_setting(10);
  Settings *my_setting3 = create_new_setting(15);
  printf("Setting1: %d\n", my_setting1->power);
  printf("Setting2: %d\n", my_setting2->power);
  printf("Setting3: %d\n", my_setting3->power);

  insert_setting(my_setting1, 1);
  insert_setting(my_setting2, 2);
  insert_setting(my_setting3, 3);
  insert_setting(my_setting2, 4);
  remove_setting(4);
  print_all_settings();

  Settings *my_setting4 = get_setting(2);
  printf("My selected setting: %p",my_setting4);
  printf("\nMy selected setting->power: %d",my_setting4->power);


  return 0;
}

// Konstruktor
Settings *create_new_setting(const int power){
  Settings *new_settings = (Settings*) malloc(sizeof(Settings));
  if (new_settings != NULL){
    new_settings->power = power;
  }
  return new_settings;
}

// Destruktor
void free_setting(Settings *setting){
  free(setting);
  setting = NULL; //przypisanie do zera dla bezpieczeństwa - uniknięcie wiszącego wskaźnika
}


void insert_setting(Settings *setting, int index){
  int i;

  // stowrzenie węzła który posiada dane oraz wskaznik na nastepny element ustawiony na NULL
  SettingsList *new_element = (SettingsList*) malloc(sizeof(SettingsList));
  new_element->settings_ptr = setting;
  new_element->next = NULL;

  // Jesli indeks jest 1 to ustaw wskaznik head na ten pierwszy element
  if (index == 1){
    new_element->next = head;
    head = new_element;
    return;
  }

  SettingsList *new_element2 = head;

  // petla ustawi wskaznik na wybrany index
  for (i=0; i<index-2; i++){
    new_element2 = new_element2->next;
  }
  new_element->next = new_element2->next;
  new_element2->next = new_element;
}


void print_all_settings(){
  SettingsList *temp = head;

  while(temp != NULL){
    // printf("%p\n", temp);
    printf("%d\n", temp->settings_ptr->power);
    temp = temp->next;
  }
  // printf("%p\n", temp);

}

void remove_setting(int index){
  int i;

  SettingsList *new_element = head;

  if (index == 1){
    head = new_element->next;
    free(new_element);
    return;
  }

  // Przesuwanie wskaznika po elementach az dojdziemy do wybranego indeksu
  for (i=0; i<index-2; i++){
    new_element = new_element->next;
  }
  SettingsList *new_element2 = new_element->next;
  new_element->next = new_element2->next;
  free(new_element2);
}


Settings *get_setting(int index){

  int i;

  SettingsList *new_element = head;

  if (index == 1){
    head = new_element->next;
    return new_element->settings_ptr;
  }

  // Przesuwanie wskaznika po elementach az dojdziemy do wybranego indeksu
  for (i=0; i<index-2; i++){
    new_element = new_element->next;
  }
  SettingsList *new_element2 = new_element->next;
  new_element->next = new_element2->next;
  return new_element2->settings_ptr;
}
