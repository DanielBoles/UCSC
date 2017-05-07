/* Author: Daniel Boles
*  Project: Lab4
*  Class: 12m
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define MAX_STRING_LENGTH 100

//global variables
   int i = 0;
   int ai,di,pi,wi;//indexes
   int lineIndex = 1;
   FILE* in;        // handle for input file                  
   FILE* out;       // handle for output file                 

// function prototypes
void extract_alpha_num(char* s, char* a);
void extract_chars(char* s, char* a, char* d, char* p, char* w);

// function main which takes command line arguments 
int main(int argc, char* argv[]){

   char* line;      // string holding input line              
   char* alpha_num; // string holding all alpha-numeric chars
   char* alph;       //string holding all alphabetical
   char* digi;       //string holding all digits
   char* punc;       //string holding all punctuation
   char* whit;       //string holding all whitespace
    

   // check command line for correct number of arguments 
   if( argc != 3 ){
      printf("Usage: %s input-file output-file\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // open input file for reading 
   if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // open output file for writing 
   if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // allocate strings line and alpha_num on the heap 
   line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   alpha_num = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   alph = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   digi = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   punc = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   whit = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   assert( line!=NULL && alpha_num!=NULL && alph != NULL && digi != NULL && punc != NULL && whit != NULL);

   // read each line in input file, extract alpha-numeric characters 
   while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
      
      //call to the function extract chars which takes whatever char is in the string and sorts them for feedback.
      extract_chars(line, alph, digi, punc, whit);

   }

   // free heap memory 
   free(line);
   free(alpha_num);
   free(alph);
   free(digi);
   free(punc);
   free(whit);


   // close input and output files 
   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;
}

// function definition 
void extract_alpha_num(char* s, char* a){
   int i=0, j=0;
   while(s[i]!='\0' && i<MAX_STRING_LENGTH){
      if( isalnum( s[i]) ) a[j++] = s[i];
      i++;
   }
   a[j] = '\0';
}

//Consider especially the functions isalnum(), isalpha(), isdigit(), 
//ispunct(), and isspace() which will be needed for this assignment
void extract_chars(char* s, char* a, char* d, char* p, char* w){
   int i = 0;

   //reset all indexes
   while(ai != i){
      a[ai] = 0;
      ai--;
   }
   while(di != i){
      d[di] = 0;
      di--;
   }
   while(pi != i){
      p[pi] = 0;
      pi--;
   }
   while(wi != i){
      w[wi] = 0;
      wi--;
   }

   //check what char is stored at s[i]
   while(s[i]!='\0' && i<MAX_STRING_LENGTH){
      if(isalpha(s[i])){
         a[ai] = s[i];
         ai++;
      }
      if(isdigit(s[i])){
         d[di] = s[i];
         di++;
      }
      
      if(ispunct(s[i])){
         p[pi] = s[i];
         pi++;
      }
      if(isspace(s[i])){
         w[wi] = s[i];
         wi++;
      }
      i++;
   }
   a[ai] = '\0';
   d[di] = '\0';
   p[pi] = '\0';
   w[wi] = '\0';

   //Output to the file
   fprintf(out, "Line %d contains:\n",lineIndex++);
   fprintf(out, "%d Alphabetic Characters: %s\n",ai,a);
   fprintf(out, "%d Digit Characters: %s\n",di,d);
   fprintf(out, "%d Punctuation Characters: %s\n",pi,p);
   fprintf(out, "%d Whitespace Characters: %s\n",wi,w);
   
}

