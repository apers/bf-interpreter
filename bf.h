#ifndef BF_H
#define BF_H
#include <stdio.h>
#define BYTE_CELL_SIZE 30000

int find_matching_left_bracket(FILE*);
int find_matching_right_bracket(FILE*);
int peek(FILE*);

#endif
