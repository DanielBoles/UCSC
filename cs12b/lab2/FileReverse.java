//Author: Daniel Boles
//Class:12m
//Lab2: FileReverse.java

// FileCopy.java
// Illustrates file IO  
import java.io.*;
import java.util.Scanner; 


 
class FileReverse{
 
//This function will return a String that is the reversal of the first 
//n characters of s
public static String stringReverse(String s, int n){

	if(n > 1){

		return s.charAt(n-1) + stringReverse(s.substring(0,(n-1)),n-1);


	}
	return s;   
}	


 public static void main(String[] args) throws IOException{

	int lineNumber = 0;
 // check number of command line arguments is at least 2      
  	if(args.length < 2){         
 	System.out.println("Usage: FileCopy <input file> <output file>");         	System.exit(1);      
 }       

// open files       
Scanner in = new Scanner(new File(args[0])); 
PrintWriter out = new PrintWriter(new FileWriter(args[1]));


// read lines from in, extract and print tokens from each line       
while( in.hasNextLine() ){
          lineNumber++;
          
// trim leading and trailing spaces, then add one trailing space so
// split works on blank lines
        String line = in.nextLine().trim() + " ";
// split line around white spaces
        String[] token = line.split("\\s+");
// print out tokens
	int n = token.length;
//	out.println("Line " + lineNumber + " contains " + n + " tokens:");
        for(int i=0; i<n; i++){
	
		token[i] = stringReverse(token[i], token[i].length());             
		out.println("  "+token[i]);
          }
       }        
 
// close files       
in.close();       
out.close();    
} 
}  


