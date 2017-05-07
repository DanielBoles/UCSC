/*
 * Matrix.java
 * Daniel Boles
 * dawboles
 * pa3
 * description: This is the test file for Matrix. 
 *
*/

public class MatrixTest{
   public static void main(String[] args){
      int i, j, n=100000;
      Matrix A = new Matrix(n);
      Matrix B = new Matrix(n);

      A.changeEntry(1,1,1); B.changeEntry(1,1,1);
      A.changeEntry(1,2,2); B.changeEntry(1,2,0);
      A.changeEntry(1,3,3); B.changeEntry(1,3,1);
      A.changeEntry(2,1,4); B.changeEntry(2,1,0);
      A.changeEntry(2,2,5); B.changeEntry(2,2,1);
      A.changeEntry(2,3,6); B.changeEntry(2,3,0);
      A.changeEntry(3,1,7); B.changeEntry(3,1,1);
      A.changeEntry(3,2,8); B.changeEntry(3,2,1);
      A.changeEntry(3,3,9); B.changeEntry(3,3,1);

      System.out.println(A.getNNZ());
      System.out.println(A);

      System.out.println(B.getNNZ());
      System.out.println(B);

      Matrix C = A.scalarMult(6);
      System.out.println(C.getNNZ());
      System.out.println(C);

      Matrix D = A.add(C);
      System.out.println(D.getNNZ());
      System.out.println(D);

      Matrix E = A.sub(D);
      System.out.println(E.getNNZ());
      System.out.println(E);

      Matrix F = B.transpose();
      System.out.println(F.getNNZ());
      System.out.println(F);

      Matrix G = B.mult(F);
      System.out.println(G.getNNZ());
      System.out.println(G);

      Matrix H = A.copy();
      System.out.println(H.getNNZ());
      System.out.println(H);
      
      A.makeZero();
      Matrix I = H.mult(A);
      System.out.println(I.getNNZ());
      System.out.println(I);
   }
}
/* OUTPUT:

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 6.0) (2, 12.0) (3, 18.0)
2: (1, 24.0) (2, 30.0) (3, 36.0)
3: (1, 42.0) (2, 48.0) (3, 54.0)

9
1: (1, 7.0) (2, 14.0) (3, 21.0)
2: (1, 28.0) (2, 35.0) (3, 42.0)
3: (1, 49.0) (2, 56.0) (3, 63.0)

9
1: (1, -6.0) (2, -12.0) (3, -18.0)
2: (1, -24.0) (2, -30.0) (3, -36.0)
3: (1, -42.0) (2, -48.0) (3, -54.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (3, 2.0)
2: (2, 1.0) (3, 1.0)
3: (1, 2.0) (2, 1.0) (3, 3.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

0
*/