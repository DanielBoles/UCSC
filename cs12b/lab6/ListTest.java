//-----------------------------------------------------------------------------
// ListTest.java
// test code for List.java
// Author: Daniel Boles
// Project: lab6
//-----------------------------------------------------------------------------

public class ListTest{
	public static void main(String[] args){

	    List<String> A = new List<String>();
	    List<String> B = new List<String>();

	    A.add(1, "One A");
	    B.add(1, "One B");
	    B.add(2, "Two B");

	    System.out.println("A = " + A);
     	System.out.println("B = " + B);

     	System.out.println("B size = " + B.size());
     	B.remove(2);
        System.out.println("B size = " + B.size());
        System.out.println("B = " + B);

     	
	}
}