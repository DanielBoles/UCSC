//-----------------------------------------------------------------------------
// DictionaryTest.c
// Test client for the Dictionary ADT
// Author: Daniel Boles
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 180

int main(int argc, char* argv[]){
   Dictionary A = newDictionary();
   char* k;
   char* v;


   char* word1[] = {"1","2","3"};
   char* word2[] = {"cat","foobar","garlicbread"};
   int i;

   for(i=0; i<strlen(word1); i++){
      insert(A, word1[i], word2[i]);
   }

   printDictionary(stdout, A);
   makeEmpty(A);
   printDictionary(stdout, A);

   for(i=0; i<strlen(word1); i++){
         insert(A, word1[i], word2[i]);
      }

   for(i=0; i<strlen(word1); i++){
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }

   insert(A, "4", "rat");

   delete(A, "2");

   printDictionary(stdout, A);

   freeDictionary(&A);

   return(EXIT_SUCCESS);
}

