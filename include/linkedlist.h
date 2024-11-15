#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node{
  char *note;
  struct Node *next;
};

struct Node *createNode(char *note);
void insert(struct Node *head, char *note);
struct Node *rotate(struct Node *root);
void freeList(struct Node *head);
int getLength(struct Node *head);

#endif