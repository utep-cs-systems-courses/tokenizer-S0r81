#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

List* init_history() {
  List *list = (List*)malloc(sizeof(List));
  list->root = NULL;
  return list;
}

void add_history(List *list, char *str) { 
  Item *new_item = (Item*)malloc(sizeof(Item));
  new_item->str = strdup(str);
  new_item->next = NULL;
  
  if(list->root == NULL) {
    new_item->id = 1;
    list->root = new_item;
  } else {
    Item *temp = list->root;
    int id = 1;
    while(temp->next != NULL) {
      temp = temp->next;
      id++;
    }
    new_item->id = id + 1;
    temp->next = new_item;
  }
}

char *get_history(List *list, int id) {
  Item *temp = list->root;
  while(temp != NULL) {
    if(temp->id == id) return temp->str;
    temp = temp->next;
  }
  return NULL;
}

void print_history(List *list) {
  Item *temp = list->root;
  while(temp != NULL) {
    printf("%d: %s\n", temp->id, temp->str);
    temp = temp->next;
  }
}

void free_history(List *list) {
  Item *current = list->root;
  Item *next;
  
  while(current != NULL) {
    next = current->next;
    free(current->str);
    free(current);
    current = next;
  }
  
  free(list);
}
