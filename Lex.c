/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA1 
* Lex.c 
* Main file for lexicographical ordering program 
**********************************************************************************/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// place(): places a word into a list
// INPUTS: array containing the words, index for the array
// element being manipulated, and the list to add it to
// OUTPUTS: void
void place (char **array, int i, List list) {
    if (length(list) == 0) {
	// empty list
        append(list, 0);
        moveFront(list);
    } else if (strcmp (array[i], array[get(list)]) <= 0) { 
	// array element goes before cursor element
        if (get(list) == front(list)) {
	    // cursor is at the front
            prepend(list, i); 
            return;
        }
        
	// move back once to compare the cursor's previous element
        movePrev(list); 
        if (strcmp (array[i], array[get(list)]) < 0) {
	    // array element goes before the cursor's previous element too... recursion 
            place(array, i, list);
        } else {
	    // array element goes before cursor and after cursor's previous element
            insertAfter(list, i);
        }
    } else {
	// array element goes after cursor element
        if (get(list) == back(list)) {
            // cursor is at the back
            append(list, i); 
            return;
        }

	// move forward once to compare cursor's next element
        moveNext(list);
        if (strcmp (array[i], array[get(list)]) > 0) {
            // array element still larger than cursor's next element... recursion
	    place(array, i, list);
        } else {
	    // array element goes after cursor but before cursor's next element
            insertBefore(list, i);
        }
    }
    return;
}


int main(int argc, char **argv) {
    // open files, make sure the number of args are correct
    if (!argv[1]) {
        fprintf(stderr, "Error: more arguments required.\n");
        exit(EXIT_FAILURE);
    }
    if (argv[3]) {
        fprintf(stderr, "Error: more arguments given than required\n");
        exit(EXIT_FAILURE);
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Error: no such input file exists.\n");
        exit(EXIT_FAILURE);
    }
    FILE *outfile = fopen(argv[2], "w");
    
    // count number of lines
    int numberOfLines = 0;
    char linereadtemp[1024] = "";
    while (fgets(linereadtemp, 1024, infile) != NULL) {
        numberOfLines += 1;
    }

    // create array where the length is the number of lines,
    // and read the file again to add the strings to the file
    fseek(infile, 0, SEEK_SET);
    char **words = malloc(numberOfLines * sizeof(char *));
    for (int i = 0; i < numberOfLines; i+=1) {
        words[i] = malloc(1024 * sizeof(char));
    }
    for (int len = 0; len < (numberOfLines); len += 1) {
        fgets(words[len], 1024, infile);
	words[len][strlen(words[len]) - 1] = '\0';
    }

    // add words to list using place() sorting algorithm
    List inlist = newList();
    for (int i = 0; i < numberOfLines; i += 1) {
        place(words, i, inlist);
    }
    
    // print out the list using my own print function
    printtofile(outfile, inlist, words);

    // close files and clear memory
    freeList(&inlist);
    for (int i = 0; i < numberOfLines; ++i) {
        free(words[i]);
    }
    free(words);
    fclose(infile);
    fclose(outfile);
    return 0;
}
     

