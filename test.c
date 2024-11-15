#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node* createNode(char *note);
void insert(struct Node *head, char *note);
void printList(struct Node *head);
int getLength(struct Node *head);
void freeList(struct Node *head);

char capitalizeNotes(char note);
int getNoteNumber(char *note);
int *getNoteSpacings(struct Node *head, int numNotes);
char *findChord(int *spacings, char *root, int numSpacings);

struct Node{
  char *note;
  struct Node *next;
};

int main(){
  struct Node *root = NULL;
  char input[128];
  int *spacings;

  printf("Enter notes (separated by spaces):\n");
  fgets(input, sizeof(input), stdin);

  // if (strcmp(input, "exit\n") == 0) {
  //   break;
  // }

  char *token = strtok(input, " \n");
  while (token != NULL) {
    token[0] = capitalizeNotes(token[0]);
    if (root == NULL) {
      root = createNode(token);  // If root is NULL, handle it separately here
    } else {
      insert(root, token);  // Insert into the existing list
    }
    token = strtok(NULL, " \n");
  }

  int note_count = getLength(root);
  
  spacings = getNoteSpacings(root, note_count);
  char *chord = findChord(spacings, root->note, note_count);

  printf("%s \n", chord);
  free(spacings);
  freeList(root);
}

struct Node* createNode(char *note){
  struct Node *new = (struct Node *)malloc(sizeof(struct Node));
  new->note = strdup(note);
  new->next = NULL;
}

void insert(struct Node *head, char *note) {
  struct Node* newNode = createNode(note);
  struct Node* temp = head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
}

void printList(struct Node *head) {
  struct Node *current = head;
  while (current != NULL) {
    printf("%s ", current->note);
    current = current->next;
  }
  printf("\n");
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

void freeList(struct Node *head) {
  struct Node *current = head;
  while (current != NULL) {
    struct Node *temp = current;
    current = current->next;
    free(temp->note);
    free(temp);
  }
}


char capitalizeNotes(char note) {
  return toupper(note);
}

// Convert note to its corresponding semitone value
int getNoteNumber(char *note) {
  char letter = note[0];
  int num;
  switch (letter) {
    case 'C': num = 0; break;
    case 'D': num = 2; break;
    case 'E': num = 4; break;
    case 'F': num = 5; break;
    case 'G': num = 7; break;
    case 'A': num = 9; break;
    case 'B': num = 11; break;
    default: return -1;
  }

  int i = 0;
  while(note[++i]){
    if (note[i] == 'b') {
      num--;
    } else if (note[i] == '#') {
      num++;
    }
  }

  return num;
}

int *getNoteSpacings(struct Node *head, int numNotes) {
  int *spacings = (int *)malloc(sizeof(int) * (numNotes - 1));
  struct Node *temp = head;
  int i = 0;
  
  while (temp != NULL && temp->next != NULL) {
    int currentNote = getNoteNumber(temp->note);
    int nextNote = getNoteNumber(temp->next->note);
    spacings[i++] = (nextNote - currentNote + 12) % 12;  // Modulo 12 to handle wrapping around
    temp = temp->next;
  }

  return spacings;
}

char *findChord(int *spacings, char *root, int numSpacings) {
  static char chord[128];

  if (spacings[0] == 4) {
    if (spacings[1] == 3) {
      snprintf(chord, sizeof(chord), "%s Major Triad", root);
    } else if (spacings[1] == 4) {
      snprintf(chord, sizeof(chord), "%s Augmented Triad", root);
    }
  } else if (spacings[0] == 3) {
    if (spacings[1] == 3) {
      snprintf(chord, sizeof(chord), "%s Diminished Triad", root);
    } else if (spacings[1] == 4) {
      snprintf(chord, sizeof(chord), "%s Minor Triad", root);
    }
  } else {
    snprintf(chord, sizeof(chord), "Unknown Chord");
  }

  return chord;
}
