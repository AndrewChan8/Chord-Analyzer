#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char capitalizeNotes(char note);
int getNoteNumber(char *note);
int *getNoteSpacings(char **notes, int numNotes);
char *findChord(int *spacings, char *root, int numSpacings);

int main(int argc, char *argv[]) {
  while(1){
    char input[128];
    char *notes[128];
    int *spacings;
    int note_count = 0;

    printf("Enter notes (separated by spaces):\n");
    fgets(input, sizeof(input), stdin);

    if (strcmp(input, "exit\n") == 0) {
      break;
    }
    char *token = strtok(input, " \n");
    while (token != NULL) {
      token[0] = capitalizeNotes(token[0]);
      notes[note_count] = token;
      note_count++;
      token = strtok(NULL, " \n");
    }

    printf("\n");

    spacings = getNoteSpacings(notes, note_count);

    char *chord = findChord(spacings, notes[0], note_count);

    printf("\nChord: %s\n", chord);

    free(spacings);
  }

  return 0;
}

char capitalizeNotes(char note) {
  return toupper(note);
}

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

  if (note[1] == 'b') {
    num--;
  } else if (note[1] == '#') {
    num++;
  }

  return num;
}

int *getNoteSpacings(char **notes, int numNotes) {
  int *spacings = (int *)malloc(sizeof(int) * (numNotes - 1));

  for (int i = 0; i < numNotes - 1; i++) {
    int currentNote = getNoteNumber(notes[i]);
    int nextNote = getNoteNumber(notes[i + 1]);

    spacings[i] = (nextNote - currentNote + 12) % 12;  // Modulo 12 to handle wrapping around
  }

  return spacings;
}

char *findChord(int *spacings, char *root, int numSpacings) {
  static char chord[128];

  if(spacings[0] == 4){
    if(spacings[1] == 3){
      snprintf(chord, sizeof(chord), "%s Major Triad", root);
    }else if(spacings[1] == 4){
      snprintf(chord, sizeof(chord), "%s Augmented Triad", root);
    }
  }else if(spacings[0] == 3){
    if(spacings[1] == 3){
      snprintf(chord, sizeof(chord), "%s Diminished Triad", root);
    }else if(spacings[1] == 4){
      snprintf(chord, sizeof(chord), "%s Minor Triad", root);
    }
  }else{
    snprintf(chord, sizeof(chord), "Unknown Chord");
  }

  return chord;
}