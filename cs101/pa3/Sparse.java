/*
 * Sparse.java
 * Daniel Boles
 * dawboles
 * pa3
 * description: This file contains main which takes input matrices and performs Matrix.java
 * library computations, then writes to the output file.
 *
*/

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

public class Sparse{

	public static void main(String[] args){
		// input check
		if(args.length!=2){
			System.err.println("Error: Invalid input");
			exit(1);
		}

		// Checks then reads the input file and creates an output.
		Scanner in = null;
		try{
			in = new Scanner(new File(args[0]));
		}
		catch(IOException except){
			System.err.println("Error: Invalid filename");
			exit(1);
		}
		PrintWriter out = null;
		try{
			out = new PrintWriter(new FileWriter(args[1]));
		}
		catch(FileNotFoundException excep){
			System.err.println("Error: Unable to create the file");
			exit(1);
		}
		catch(IOException excep){
			System.err.println("Error: Unable to create the file");
			exit(1);
		}

		int check = intCheck(in);
		Matrix A = new Matrix(check);
		Matrix B = new Matrix(check);
		int A1 = intCheck(in);
		int B1 = intCheck(in);
		
		// Here we build the two Matrices A and B
		in.nextLine();
		for(;A1 > 0; A1--){
			A.changeEntry(intCheck(in), intCheck(in), in.nextDouble());
		}
		out.println("A has " +A.getNNZ() +" non-zero entries:");
		out.println(A);

		in.nextLine();
		for(;B1 > 0; B1--){
			B.changeEntry(intCheck(in), intCheck(in), in.nextDouble());
		}
		out.println("B has " +B.getNNZ() +" non-zero entries:");
		out.println(B);

		// Now begin the computations for output
		Matrix C = A.scalarMult(1.5); 
		out.println("(1.5)*A ="); 
		out.println(C); 

		Matrix D = A.add(B); 
		out.println("A+B ="); 
		out.println(D); 
		 
		Matrix E = A.add(A); 
		out.println("A+A ="); 
		out.println(E); 
		 
		Matrix F = B.sub(A); 
		out.println("B-A ="); 
		out.println(F); 
		 
		Matrix G = A.sub(A); 
		out.println("A-A ="); 
		out.println(G); 
		 
		Matrix H = A.transpose(); 
		out.println("Transpose(A) ="); 
		out.println(H); 

		Matrix I = A.mult(B); 
		out.println("A*B ="); 
		out.println(I); 

		Matrix J = B.mult(B); 
		out.println("B*B ="); 
		out.println(J); 

		out.close();
	}

	// Helper function to check if there is integers remaining in the file for input to build the matrices
	static int intCheck(Scanner file){
		int check = 0;
		if(file.hasNextInt()){
			check = file.nextInt();
		}
		else{
			System.out.println("Error: invalid file input format for integer checking");
			exit(1);
		}
		return check;
	}

}

