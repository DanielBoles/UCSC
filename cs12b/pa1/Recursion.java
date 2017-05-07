//Author: Daniel Boles
//CruzID: dawboles
//Class: 12B

//-----------------------------------------------------------------------------
// Recursion.java
// Template for CMPS 12B pa1.  Fill in the five recursive functions below.
//-----------------------------------------------------------------------------

class Recursion {
   
   // reverseArray1()
   // Places the leftmost n elements of X[] into the rightmost n positions in
   // Y[] in reverse order
   static int reverseArray1(int[] X, int n, int[] Y){
      // if n==0 do nothing
     
      if(n > 0) { 
         //System.out.print(X[n-1] + " "); // print nth element from left
         Y[X.length-n] = X[n-1];
         //System.out.print("  Y=" + Y[n-1]); // print nth element from left
        
         return reverseArray1(X, n-1, Y);          // print leftmost n-1 elements, reversed
      }
return 0;
   }

//    reverseArray2()
//    Places the rightmost n elements of X[] into the leftmost n positions in
//    Y[] in reverse order.
   static int reverseArray2(int[] X, int n, int[] Y){
     if(n > 0){
       
       Y[n-1] = X[X.length-n];
       
       return reverseArray2(X, n-1, Y);
     }
     return 0;
   }
//   
//    reverseArray3()
//    Reverses the subarray X[i...j].
   static int reverseArray3(int[] X, int i, int j){
     int hold = 0;
  
     if(i < j){
       hold = X[i];
       X[i] = X[j];
       X[j] = hold;
       return reverseArray3(X, i+1, j-1);
     }
return 0;
   }
   
//    maxArrayIndex()
//    returns the index of the largest value in int array X
   static int maxArrayIndex(int[] X, int p, int r){
     int q;
     int left, right;
     if(r == p){
       return r;
     }
     if(r > p){
       q = (p+r)/2;
       left = maxArrayIndex(X, p, q);
       
       right = maxArrayIndex(X, q+1, r);
       if(X[left] > X[right]){
         return left;
       }else{
       return right;
       }
     }  
     else{
         return 0;
   }
   }     
//    minArrayIndex()
//    returns the index of the smallest value in int array X
   static int minArrayIndex(int[] X, int p, int r){
     int q;
     int left, right;
     if(r == p){
       return r;
     }
     if(r > p){
       q = (p+r)/2;
       left = minArrayIndex(X, p, q);
       
       right = minArrayIndex(X, q+1, r);
       if(X[left] < X[right]){
         return left;
       }else{
       return right;
       }
     }  
     else{
         return 0;
   }

   }
   
   // main()
   public static void main(String[] args){
      
      int[] A = {-1, 2, 6, 12, 9, 2, -5, -2, 8, 5, 7};
      int[] B = new int[A.length];
      int[] C = new int[A.length];
      int minIndex = minArrayIndex(A, 0, A.length-1);
      int maxIndex = maxArrayIndex(A, 0, A.length-1);
      
      for(int x: A) System.out.print(x+" ");
      System.out.println(); 
      
      System.out.println( "minIndex = " + minIndex );  
      System.out.println( "maxIndex = " + maxIndex );  

      reverseArray1(A, A.length, B);
      for(int x: B) System.out.print(x+" ");
      System.out.println();
      
      reverseArray2(A, A.length, C);
      for(int x: C) System.out.print(x+" ");
      System.out.println();
      
      reverseArray3(A, 0, A.length-1);
      for(int x: A) System.out.print(x+" ");
      System.out.println();  
      
   }
   
}
/* Output:
-1 2 6 12 9 2 -5 -2 8 5 7
minIndex = 6
maxIndex = 3
7 5 8 -2 -5 2 9 12 6 2 -1
7 5 8 -2 -5 2 9 12 6 2 -1
7 5 8 -2 -5 2 9 12 6 2 -1
*/
