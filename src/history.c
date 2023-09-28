#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

List* init_history() {
    List *list = (List*)malloc(sizeof(List));
    list->root = NULL;
    return list;
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str){
    Node *node = (Node*)malloc(sizeof(Node));
    node->str = str;
    node->next = NULL;
    if(list->root == NULL){
        list->root = node;
    } else {
        Node *curr = list->root;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = node;
    }
}


/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str){
    Node *node = (Node*)malloc(sizeof(Node));
    node->str = str;
    node->next = NULL;
    if(list->root == NULL){
        list->root = node;
    } else {
        Node *curr = list->root;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = node;
    }
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id){
    Node *curr = list->root;
    while(curr != NULL){
        if(curr->id == id){
            return curr->str;
        }
        curr = curr->next;
    }
    return NULL;
}

/*Print the entire contents of the list. */
void print_history(List *list){
    Node *curr = list->root;
    while(curr != NULL){
        printf("%d: %s\n", curr->id, curr->str);
        curr = curr->next;
    }
}

/*Free the history list and the strings it references. */
void free_history(List *list){
    Node *curr = list->root;
    while(curr != NULL){
        Node *next = curr->next;
        free(curr->str);
        free(curr);
        curr = next;
    }
    free(list);
}