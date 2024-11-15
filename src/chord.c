#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linkedlist.h"
#include "../include/chord.h"
#include "../include/utils.h"

int *getNoteSpacings(struct Node *head, int numNotes) {
  int *spacings = (int *)malloc(sizeof(int) * (numNotes - 1));
  struct Node *temp = head;
  int i = 0;
  
  while (temp != NULL && temp->next != NULL) {
    int currentNote = getNoteNumber(temp->note);
    int nextNote = getNoteNumber(temp->next->note);
    spacings[i++] = (nextNote - currentNote + 12) % 12; // Modulo 12 to handle wrapping around
    temp = temp->next;
  }

  return spacings;
}

char *findChord(int *spacings, char *root, int numSpacings) {
  char *chord = (char *)malloc(CHORD_SIZE * sizeof(char));

  if(spacings[0] == 4){
    if(spacings[1] == 3){
      snprintf(chord, CHORD_SIZE, "%s Major Triad", root);
    }else if(spacings[1] == 4){
      snprintf(chord, CHORD_SIZE, "%s Augmented Triad", root);
    }else{
      snprintf(chord, CHORD_SIZE, "Unknown Chord");
    }
  }else if(spacings[0] == 3){
    if(spacings[1] == 3){
      snprintf(chord, CHORD_SIZE, "%s Diminished Triad", root);
    }else if(spacings[1] == 4){
      snprintf(chord, CHORD_SIZE, "%s Minor Triad", root);
    }else{
      snprintf(chord, CHORD_SIZE, "Unknown Chord");
    }
  }else{
    snprintf(chord, CHORD_SIZE, "Unknown Chord");
  }

  return chord;
}
