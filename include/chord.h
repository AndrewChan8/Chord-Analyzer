#ifndef CHORD_H
#define CHORD_H

#define CHORD_SIZE 128

int *getNoteSpacings(struct Node *head, int numNotes);
char *findChord(int *spacings, char *root, int numSpacings);

#endif
