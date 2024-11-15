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

typedef struct{
  int intervals[3];
  const char* chord_name;
} SeventhPatterns;

TriadPatterns triad_patterns[] = {
  {{4, 3}, "Major Triad"},
  {{3, 4}, "Minor Triad"},
  {{3, 3}, "Diminished Triad"},
  {{4, 4}, "Augmented Triad"},
  {{2, 5}, "Sus2 Triad"},
  {{5, 2}, "Sus4 Triad"}
};

SeventhPatterns chord_patterns[] = {
  {{4, 3, 4}, "Major 7th"},
  {{4, 3, 3}, "Dominant 7th"},
  {{3, 4, 3}, "Minor 7th"},
  {{3, 3, 3}, "Diminished 7th"},
  {{3, 3, 4}, "Half-Diminished 7th"},
  {{4, 4, 3}, "Augmented Major 7th"},
  {{4, 4, 2}, "Augmented 7th"},
  {{3, 4, 4}, "Minor Major 7th"},
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

  if (numSpacings == 2) {
    for (int i = 0; i < sizeof(triad_patterns) / sizeof(triad_patterns[0]); i++) {
      if (spacings[0] == triad_patterns[i].intervals[0] &&
          spacings[1] == triad_patterns[i].intervals[1]) {
        snprintf(chord, CHORD_SIZE, "%s %s", root, triad_patterns[i].chord_name);
        return chord;
      }
    }
  }

  // if (numSpacings == 3) {
  //   for (int i = 0; i < sizeof(chord_patterns) / sizeof(chord_patterns[0]); i++) {
  //     if (spacings[0] == chord_patterns[i].intervals[0] &&
  //         spacings[1] == chord_patterns[i].intervals[1] &&
  //         spacings[2] == chord_patterns[i].intervals[2]) {
  //       snprintf(chord, CHORD_SIZE, "%s %s", root, chord_patterns[i].chord_name);
  //       return chord;
  //     }
  //   }
  // }

  snprintf(chord, CHORD_SIZE, "Unknown Chord");
  return chord;
}
