#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linkedlist.h"

struct Node *createNode(char *note){
  struct Node *new = (struct Node *)malloc(sizeof(struct Node));
  new->note = strdup(note);
  new->next = NULL;
  return new;
}

void insert(struct Node *head, char *note) {
  struct Node* newNode = createNode(note);
  struct Node* temp = head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
}

struct Node *rotate(struct Node *root){
  if (root == NULL || root->next == NULL) {
    return root;
  }

  struct Node *oldRoot = root;
  struct Node *newRoot = root->next;

  struct Node* current = root;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = oldRoot;
  oldRoot->next = NULL;

  return newRoot;
}

void freeList(struct Node *head) {
  struct Node *current = head;
  while (current != NULL) {
    struct Node *temp = current;
    current = current->next;
    free(temp->note);
    free(temp);
  }
}

int getLength(struct Node *head){
  int count = 0;
  struct Node *temp = head;
  while(temp != NULL){
    temp = temp->next;
    count++;
  }
  return count;
}
