#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linkedlist.h"
#include "../include/chord.h"
#include "../include/utils.h"

typedef struct{
  int intervals[2];
  const char* chord_name;
} TriadPatterns;

TriadPatterns chord_patterns[] = {
  {{4, 3}, "Major Triad"},
  {{3, 4}, "Minor Triad"},
  {{3, 3}, "Diminished Triad"},
  {{4, 4}, "Augmented Triad"},
  {{2, 5}, "Sus2 Triad"},
  {{5, 2}, "Sus4 Triad"},
};

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

  for (int i = 0; i < sizeof(chord_patterns) / sizeof(chord_patterns[0]); i++) {
    if (spacings[0] == chord_patterns[i].intervals[0] &&
        spacings[1] == chord_patterns[i].intervals[1]) {
      snprintf(chord, CHORD_SIZE, "%s %s", root, chord_patterns[i].chord_name);
      return chord;
    }
  }

  snprintf(chord, CHORD_SIZE, "Unknown Chord");
  return chord;
}
