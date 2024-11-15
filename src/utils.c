#include <stdio.h>
#include <ctype.h>
#include "../include/utils.h"

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
