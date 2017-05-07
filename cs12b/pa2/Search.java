/* Author: Daniel Boles
 * Class: 12b
 * PA2: Search.java
 */


import java.io.*;
import java.util.Scanner;

public class Search {

  // mergeSort()
   // sort subarray A[p...r]
   public static void mergeSort(String[] word, int[] lineNumber, int p, int r){
      int q;
      
      if(p < r) {
         q = (p+r)/2;
         // System.out.println(p+" "+q+" "+r);
         mergeSort(word, lineNumber, p, q);
         mergeSort(word, lineNumber, q+1, r);
         merge(word, lineNumber, p, q, r);
      }
   }

   // merge()
   // merges sorted subarrays A[p..q] and A[q+1..r]
   public static void merge(String[] word, int[] lineNumber, int p, int q, int r){
      
      int n1 = q-p+1;

      int n2 = r-q;
      String[] L = new String[n1];
      String[] R = new String[n2];
      
      int[] LI = new int[n1];
      int[] RI = new int[n2];
      
      int i, j, k;

      for(i=0; i<n1; i++){
         L[i] = word[p+i];
         LI[i] = lineNumber[p+i];
         
      }
      for(j=0; j<n2; j++){
         R[j] = word[q+j+1];
         RI[j] = lineNumber[q+j+1];
         
      }

      i = 0; j = 0;
      for(k=p; k<=r; k++){
         if( i<n1 && j<n2 ){
            if( L[i].compareTo(R[j])<0 ){
               word[k] = L[i];
               lineNumber[k] = LI[i];
               i++;
            }else{
               word[k] = R[j];
               lineNumber[k] = RI[j];
               j++;
            }
         }else if( i<n1 ){
            word[k] = L[i];
            lineNumber[k] = LI[i];
            i++;
         }else{ // j<n2
            word[k] = R[j];
            lineNumber[k] = RI[j];
            j++;
         }
      }
   }

   // binarySearch()
   // pre: Array A[p..r] is sorted
   static int binarySearch(String[] word, int p, int r,  String target){
      int q;
 
      if(p > r) {
         return -1;
      }else{
         q = (p+r)/2;
         if(target.compareTo(word[q]) == 0){
            return q;
         }else if(target.compareTo(word[q]) < 0){
            return binarySearch(word, p, q-1, target);
         }else{ // target > A[q]
            return binarySearch(word, q+1, r, target);
         }
      }
   }

   
public static void main(String[] args) throws IOException{

int  i;

 // check number of command line arguments
      if(args.length < 2){
         System.err.println("Usage: LC file");
         System.exit(1);
      }
      
      // count the number of lines in file
      Scanner in = new Scanner(new File(args[0]));
      in.useDelimiter("\\Z"); // matches the end of file character
      String s = in.next();  // read in whole file as a single String
      in.close();
      String[] lines = s.split("\n");  // split s into individual lines
      int lineCount = lines.length;  // extract length of the resulting array
      


i=0;
int[] lineNumber = new int[lineCount];
for(i = 0; i < lineCount; i++){
  lineNumber[i] = i;
}

mergeSort(lines, lineNumber, 0, lineCount-1);


for(i=1; i < args.length; i++){
  String target = args[i];
  int ret = binarySearch(lines, 0, lineCount-1, target);
  if (ret < 0){
    System.out.println(target + " not found");
  }else{
    
  System.out.println(args[i] + " found on line " + (lineNumber[ret]+1));
}
}
}
}
