/*
 *
 * A simple brainfuck interpreter
 *
 * */

#include "bf.h"

/* The byte cells */
char cells[BYTE_CELL_SIZE];

/* Pointer to the first cell */
char *ptr = cells;


int main(int argc, char** argv) {
    char cur_symbol;


    if( argc != 2 ) {
        fprintf(stderr, "Usage: ./bf <inputfile>\n");
    }

    /* Open file  */
    FILE *fp = fopen(argv[1], "r");     
    if( fp == NULL  ) {
        fprintf(stderr, "Could not open file: %s\n", argv[1]);
        return 1;
    }

    /* Main interpreter loop */
    while( (cur_symbol = fgetc(fp)) != EOF  ) {
        switch(cur_symbol) {
            case '>': /* Increment pointer */
                ptr++;
                break;
            case '<': /* Decrement pointer */
                ptr--;
                break;
            case '+': /* Increment value of pointer */
                ++*ptr;
                break;
            case '-': /* Decrement value of pointer */
                --*ptr;
                break;
            case '.': /* Output char value of pointer */
                putchar(*ptr);
                break;
            case ',': /* Take input */
                *ptr = getchar(); 
                break;
            case '[': /* if *ptr==0 jump to ]  */
                /* This will jump the IP forward */
                if( *ptr == 0  ) {
                    find_matching_right_bracket(fp);
                }
                break;
            case ']': /* if *ptr!=0 jump back to ] */
                /* This will jump the IP backward */
                if( *ptr != 0  ) {
                    find_matching_left_bracket(fp);
                } 
                break;
        }
    }

    return 0;
}

/* Finds the mathcing ]   
 *
 * Returns 0 if a matching bracket is found
 * Return 1 if EOF is found before a mathcing bracket 
 *
 * */
int find_matching_right_bracket(FILE *fp) {
    int bracket_cnt = 1;
    int cur_symbol;

    /* Loop until we find a matching bracket */
    while( (cur_symbol = fgetc(fp)) != EOF  ) {
        switch(cur_symbol) {
            case '[':
                bracket_cnt++;
                break;
            case ']':
                bracket_cnt--;
                break;
        }

        /* If bracket count is 0 we found the  mathcing bracket */
        if( bracket_cnt == 0 ) {
            return 0;
        }
    }

    /* EOF found before matching bracket */
    return 1;

}

/* Finds the matching [ */
int find_matching_left_bracket(FILE *fp) {
    int bracket_cnt = 0;

    while(1) {
        /* Jump one position back */ 
        fseek(fp, -1, SEEK_CUR);
        
        /* Check for brackets */
        if( peek(fp) == ']' ) {
            bracket_cnt++;
        } else if( peek(fp) == '[' ) {
            bracket_cnt--;
        }

        /* Mathcing bracket found */
        if( bracket_cnt == 0 ) {
            /* Skip matching bracket */
            fgetc(fp); 

            return 0;
        }
    }
}

/* Peeks at the character in the stream */
int peek(FILE *fp) {
    int c = fgetc(fp);
    ungetc(c, fp);
    return c;
}
