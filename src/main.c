#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linkedlist.h"
#include "../include/chord.h"
#include "../include/utils.h"

int main(){
  while(1){
    struct Node *root = NULL;
    char input[128];
    int *spacings;

    printf("Enter notes (separated by spaces):\n");
    fgets(input, sizeof(input), stdin);

    if (strcmp(input, "exit\n") == 0) {
      break;
    }

    char *token = strtok(input, " \n");
    while (token != NULL) {
      token[0] = capitalizeNotes(token[0]);
      if (root == NULL) {
        root = createNode(token);
      } else {
        insert(root, token);
      }
      token = strtok(NULL, " \n");
    }

    int note_count = getLength(root);
    char *chord;
    int i = 0;
    while(i < note_count){
      spacings = getNoteSpacings(root, note_count);

      chord = findChord(spacings, root->note, note_count);
      if(strcmp(chord, "Unknown Chord") == 0){
        i++;
        root = rotate(root);
      }else{
        break;
      }
    }

    char *newChord = (char *)malloc(CHORD_SIZE * sizeof(char));

    if(i == 1){
      snprintf(newChord, CHORD_SIZE, "%s (2nd Inversion)", chord);
      printf("%s \n", newChord);
    }else if(i == 2){
      snprintf(newChord, CHORD_SIZE, "%s (1st Inversion)", chord);
      printf("%s \n", newChord);
    }else{
      printf("%s \n", chord);
    }

    free(newChord);
    free(spacings);
    free(chord);
    freeList(root);
  }
}
