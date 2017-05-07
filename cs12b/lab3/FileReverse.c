/* Author: Daniel Boles
*  Project: Lab3
*  Class: 12m
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *  FileIO.c *  Reads input file and prints each word on a separate line of *  the output file. */
#include<stdio.h> 
#include<stdlib.h>  

//Declare global variables
int i, j;
char hold[1];


//The function swap takes value at index i and swaps it with value at index j
static void swap(int i, int j, char hold[1], char arr[]){

	hold[0] = arr[i];
	arr[i] = arr[j];
	arr[j] = hold[0];
	
	return;
}

//This function has a loop that switches all letters in the word string
//into reverse order
static void stringReverse(char* word){

		for(i = 0, j = strlen(word)-1; i < j+1; i++, j--){
			swap(i,j,hold,word);

		}
		return;
}
int main(int argc, char* argv[])
{
    FILE* in;
    /* file handle for input */
    FILE* out;
    /* file handle for output */
    char word[256];
    /* char array to store words from input file */

    /* check command line for correct number of arguments */
    if (argc != 3) {

        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* open input file for reading */
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    /* open output file for writing */ out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    /* read words from input file, print on separate lines to output file*/
    while (fscanf(in, " %s", word) != EOF) {

    	stringReverse(word);
		
        fprintf(out, "%s\n", word);
    }
    /* close input and output files */
    fclose(in);
    fclose(out); 

	// end of fileIO.c

	return EXIT_SUCCESS;
}



