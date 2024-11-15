#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void capitalizeNotes(char *note);
int getNoteNumber(char *note);
int *getNoteSpacings(struct Node *head, int numNotes);
char *findChord(int *spacings, char *root, int numSpacings);
void cycleLeft(struct Node **head);
struct Node* createNode(char *note);
void insert(struct Node **head, char *note);
void printList(struct Node *head);

struct Node{
  char *note;
  struct Node *next;
};

int main(int argc, char *argv[]) {
  while(1){
    struct Node *root = NULL;
    char input[128];
    int *spacings;
    int note_count = 0;

    printf("Enter notes (separated by spaces):\n");
    fgets(input, sizeof(input), stdin);

    if (strcmp(input, "exit\n") == 0) {
      break;
    }

    // Tokenize the input and insert into the linked list
    char *token = strtok(input, " \n");
    while (token != NULL) {
      capitalizeNotes(token);  // Capitalize the note
      insert(&root, token);
      note_count++;
      token = strtok(NULL, " \n");
    }

    printf("\n");

    // Traverse the linked list to collect the notes into an array for processing
    struct Node *temp = root;
    char *notes[128];
    int i = 0;
    while (temp != NULL) {
      notes[i++] = temp->note;
      temp = temp->next;
    }

    spacings = getNoteSpacings(root, note_count);

    // Find the chord by cycling through possible inversions
    char *chord;
    int j = 0;
    while (j < note_count) {
      chord = findChord(spacings, notes[0], note_count);
      if (strcmp(chord, "Unknown Chord") == 0) {
        j++;
        cycleLeft(&root);  // Rotate the linked list to simulate inversion
        temp = root;
        i = 0;
        // Rebuild the notes array after modifying the linked list
        while (temp != NULL) {
          notes[i++] = temp->note;
          temp = temp->next;
        }
      } else {
        break;
      }
    }

    printf("\nChord: %s\n", chord);

    free(spacings);
  }

  return 0;
}

// Capitalize the notes
void capitalizeNotes(char *note) {
  for (int i = 0; note[i]; i++) {
    note[i] = toupper(note[i]);  // Convert each character to uppercase
  }
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

void cycleLeft(struct Node **head) {
  if (*head == NULL || (*head)->next == NULL) return;

  struct Node *first = *head;
  struct Node *temp = *head;

  while (temp->next != NULL) {
    temp = temp->next;
  }

  // Move the first node to the end
  *head = (*head)->next;  // Update the head to the next node
  temp->next = first;     // Attach the first node to the end
  first->next = NULL;     // Set the next of the first node to NULL
}

void insert(struct Node **head, char *note){
  struct Node *newNode = createNode(note);
  if (*head == NULL) {
    *head = newNode;
    return;
  }
  struct Node *temp = *head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
}

struct Node* createNode(char *note){
  struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->note = strdup(note);
  newNode->next = NULL;
  return newNode;
}
