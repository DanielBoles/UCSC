/*
 * Matrix.java
 * Daniel Boles
 * dawboles
 * pa3
 * description: This is the library of functions used to perform matrix math on the 
 * object oriented List.
 *
*/

// Constructor 
public class Matrix{
	private class Entry{
		int column;
		double value;
		Entry(int col, double val){
			column = col;
			value = val;
		}
		public boolean equals(Object x){
			if(x == null || !(x instanceof Entry)){
				return false;
			}
			if(x == this){
				return true;
			}
			Entry hold = (Entry)x;
			if(this.column == hold.column && this.value == hold.value){
				return true;
			}
			else return false;
		}
		public String toString(){
			return "(" + column + ", " + value + ")";
		}
	}
	private List[] matrix;
	private int NNZ;

	// Makes a new n x n zero Matrix.  pre: n>=1  
	public Matrix(int n){
		if(n<1){
			System.out.println("Error: invalid matrix size");
			throw new RuntimeException();
		}
		matrix = new List[n];
		for(int i = 0; i < n; i++){
			matrix[i] = new List();
		}
		NNZ = 0;
	}

	// Access functions
	// Returns n, the number of rows and columns of this Matrix  
	int getSize(){
		return matrix.length;
	}
	// Returns the number of non-zero entries in this Matrix
	int getNNZ(){
		return NNZ;
	}  
	// overrides Object's equals() method  
	public boolean equals(Object x){
		if(x == null || !(x instanceof Matrix)){
			System.out.println("Error: invalid matrix input for equals");
			return false;
		}
		Matrix hold = (Matrix)x;
		if(hold.getSize() != matrix.length){
			return false;
		}
		for(int i = 0; i< matrix.length; i++){
			if(!(matrix[i].equals(hold.matrix[i]))){
				return false;
			}
		}
		return true;
	}

	// Manipulation procedures
	// sets this Matrix to the zero state   
	void makeZero(){
		NNZ = 0;
		for(int i = 0; i< matrix.length; i++){
			matrix[i].clear();
		}
	}
	// returns a new Matrix having the same entries as this Matrix
	Matrix copy(){
 		Matrix newCopy = new Matrix(matrix.length);
 		for(int row = 0; row < matrix.length; row++){
 			List past = matrix[row];
 			List present = newCopy.matrix[row];
 			if(past.length() > 0){
 				past.moveFront();
 			}
 			for(; past.index() >= 0; past.moveNext()){
 				Object obj = past.get();
 				if(obj == null || !(obj instanceof Entry)){
 					System.out.println("Error: Invalid type for copy");
 					return null;
 				}
 				Entry x = (Entry)obj;
 				Entry xCopy = new Entry(x.column, x.value);
 				present.append(xCopy);
 			}
 		}
 		newCopy.NNZ = NNZ;
 		return newCopy;
	}   
	// changes ith row, jth column of this Matrix to x 
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x){
		if((i+j) > 2 * matrix.length || (i+j) < 2){
			System.out.println("Error: Invalid Index parameter");
			return;
		}
		List row = matrix[i - 1];
		if(row == null){
			System.out.println("Error: Invalid row parameter");
			return;
		}
		Entry change = null;
		if(row.length() > 0){
			row.moveFront();
		}
		for(; row.index() >= 0; row.moveNext()){
			Object obj = row.get();
			if(obj == null || !(obj instanceof Entry)){
				System.out.println("Error: Invalid type for changeEntry");
				return;
			}
			change = (Entry)obj;
			if(change.column < j){
				continue;
			}
			break;
		}
		if(row.index() == -1 && x != 0){
			row.append(new Entry(j, x));
			NNZ++;
		}
		else if(change != null && change.column == j){
			if(x == 0){
				row.delete();
				NNZ--;
			}
			else{
				change.value = x;
			}
		}
		else{
			if(x != 0){
				row.insertBefore(new Entry(j, x));
				NNZ++;
			}
		}
	}      
	// returns a new Matrix that is the scalar product of this Matrix with x 
	Matrix scalarMult(double x){
		if(x == 0){
			this.makeZero();
		}
		Matrix newCopy = new Matrix(matrix.length);
		for(int i = 0; i < matrix.length; i++){
			List past = matrix[i];
			List present = newCopy.matrix[i];
			if(past.length() > 0){
				past.moveFront();
			}
			for(; past.index() >=0; past.moveNext()){
				Object obj = past.get();
 				if(obj == null || !(obj instanceof Entry)){
 					System.out.println("Error: Invalid type for scalarMult");
 					return null;
 				}
 				Entry x1 = (Entry)obj;
 				Entry x1Copy = new Entry(x1.column, x1.value * x);
 				present.append(x1Copy);
 			}
 		}
 		newCopy.NNZ = NNZ;
 		return newCopy;
	}
	 // returns a new Matrix that is the sum of this Matrix with M     
	 // pre: getSize()==M.getSize() 
	Matrix add(Matrix M){
		if(!(this.getSize() == M.getSize())){
			System.out.println("Error: Incompatible matrix sizes for add");
			return null;
		}
		if(this == M){
			return this.scalarMult(2);
		}
		Matrix newCopy = new Matrix(matrix.length);
		for(int i = 0; i < matrix.length; i++){
			List a = matrix[i];
			List b = M.matrix[i];
			List sum = newCopy.matrix[i];
			if(a.length() > 0){
				a.moveFront();
			}
			if(b.length() > 0){
				b.moveFront();
			}
			while(a.index() >= 0 && b.index() >= 0){
				Entry a1 = (Entry)(a.get());
				Entry b1 = (Entry)(b.get());
				newCopy.NNZ++;
				if(a1.column == b1.column){
					if(a1.value + b1.value != 0){
						sum.append(new Entry(a1.column, a1.value + b1.value));
					}
					else{
						NNZ--;
					}
					a.moveNext();
					b.moveNext();
				}
				else if(a1.column < b1.column){
					sum.append(new Entry(a1.column, a1.value));
					a.moveNext();
				}
				else{
					sum.append(new Entry(b1.column, b1.value));
					b.moveNext();
				}
			}
			if(a.index() == b.index()){
				continue;
			}
			List remaining = (a.index()>=0)? a : b;
			while(remaining.index() >= 0 ){
				Entry finished = (Entry)(remaining.get());
				newCopy.NNZ++;
				sum.append(new Entry(finished.column, finished.value));
				remaining.moveNext();
			}
		}
		return newCopy;
	}
	// returns a new Matrix that is the difference of this Matrix with M     
	// pre: getSize()==M.getSize()
	Matrix sub(Matrix M){
		if(!(this.getSize() == M.getSize())){
			System.out.println("Error: Incompatible matrix sizes for sub");
			return null;
		}
		if(this == M){
			return new Matrix(matrix.length);
		}
		Matrix newCopy = new Matrix(matrix.length);
		for(int i = 0; i < matrix.length; i++){
			List a = matrix[i];
			List b = M.matrix[i];
			List dif = newCopy.matrix[i];
			if(a.length() > 0){
				a.moveFront();
			}
			if(b.length() > 0){
				b.moveFront();
			}
			while(a.index() >= 0 && b.index() >= 0){
				Entry a1 = (Entry)(a.get());
				Entry b1 = (Entry)(b.get());
				newCopy.NNZ++;
				if(a1.column == b1.column){
					if(a1.value - b1.value != 0){
						dif.append(new Entry(a1.column, a1.value - b1.value));
					}
					else{
						NNZ--;
					}
					a.moveNext();
					b.moveNext();
				}
				else if(a1.column < b1.column){
					dif.append(new Entry(a1.column, a1.value));
					a.moveNext();
				}
				else{
					dif.append(new Entry(b1.column, 0 - b1.value));
					b.moveNext();
				}
			}
			if(a.index() == b.index()){
				continue;
			}
			List remaining = (a.index()>=0)? a : b;
			int sign = (a.index()>=0)? 1 : -1;
			while(remaining.index() >= 0 ){
				Entry finished = (Entry)(remaining.get());
				newCopy.NNZ++;
				dif.append(new Entry(finished.column, finished.value * sign));
				remaining.moveNext();
			}
		}
		return newCopy;
	}      
	// returns a new Matrix that is the transpose of this Matrix 
	Matrix transpose(){
		Matrix newCopy = new Matrix(matrix.length);
		for(int i = 0; i < matrix.length; i++){
			List row = matrix[i];
			if(row.length() > 0){
				row.moveFront();
			}
			for(; row.index() >= 0; row.moveNext()){
				Entry newEntry = (Entry)(row.get());
				int line = newEntry.column - 1;
				newCopy.matrix[line].append(new Entry(i + 1, newEntry.value));
			}
		}
		newCopy.NNZ = NNZ;
		return newCopy;
	}
	// returns a new Matrix that is the product of this Matrix with M     
	// pre: getSize()==M.getSize()     
	Matrix mult(Matrix M){
		if(!(this.getSize() == M.getSize())){
			System.out.println("Error: Incompatible matrix sizes for mult");
			return null;
		}
		Matrix newCopy = new Matrix(matrix.length);
		if(this.NNZ == 0 || M.NNZ == 0){
			return newCopy;
		}
		Matrix tran = M.transpose();
		for(int i = 0; i < matrix.length; i++){
			if(matrix[i].length() == 0){
				continue;
			}
			for(int j = 0; j < matrix.length; j++){
				if(tran.matrix[j].length() == 0){
					continue;
				}
				double result = dot(matrix[i], tran.matrix[j]);
				if(result != 0){
					newCopy.matrix[i].append(new Entry(j + 1, result));
					newCopy.NNZ++;
				}
			}
		}
		return newCopy;
	}

	// Other functions  
	// overrides Object's toString() method
	public String toString(){
		String newCopy = "";
		for(int i = 0; i < matrix.length; i++){
			if(matrix[i].length() > 0){
				newCopy += (i+1) + ": " + matrix[i] + "\n";
			}
		}
		return newCopy;
	} 
	//computes the vector dot product of two matrix rows represented by Lists P and Q
	private static double dot(List P, List Q){
		double result = 0;
		P.moveFront();
		Q.moveFront();
		while(P.index() >= 0 && Q.index() >= 0){
			Entry p = (Entry)(P.get());
			Entry q = (Entry)(Q.get());
			if(p.column == q.column){
				result += p.value * q.value;
				P.moveNext();
				Q.moveNext();
			}
			else if(p.column < q.column){
				P.moveNext();
			}
			else{
				Q.moveNext();
			}
		}
		return result;
	}
}