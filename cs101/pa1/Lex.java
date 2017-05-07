/*
 * Lex.java
 * Daniel Boles
 * dawboles
 * pa1
 * description: Sorting algorithm for List. Contains main.
 *
*/

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

public class Lex{
	
	// Countss how many words are within the input file.
	static int wordCount(Scanner file){
		int count = 0;
		for(count=0; file.hasNext(); file.next()){
			count++;
		}
		return count;
	}

	// Reads the string of words and outputs an array of the words
	static String[] read(Scanner file, int words){
		String[] arr = new String[words];
		for(int i = 0; file.hasNext(); i++){
			arr[i] = file.next();
		}
		return arr;
	}

	// Here the lexographic sorting algorithm happens based on insertion sort.
	static List insertionSort(String[] file){
		List list = new List();
		if(file.length > 0){
			list.append(0);
		}
		
		for(int i = 1; i < file.length; i++){

			String hold = file[i];
			int index = i-1;
			list.moveFront();

			while(list.index() >= 0 && hold.compareTo(file[list.get()]) < 1){
				
				index--;
				list.movePrev();
			}
			if(list.index() == -1){
				
				list.prepend(i);
			}
			else{
				
				list.insertAfter(i);
			}
		}
		return list;
	}

	// Main opens the input and output files, performs the sort on the in, then writes to
	// the output file in lexographic order.
	public static void main(String[] args){
		if(args.length!=2){
			System.err.println("Error: Invalid input");
			exit(1);
		}
		Scanner in = null;
		try{
			in = new Scanner(new File(args[0]));
		}
		catch(IOException except){
			System.err.println("Error: Invalid filename");
			exit(1);
		}
		PrintWriter write = null;
		try{
			write = new PrintWriter(new FileWriter(args[1]));
		}
		catch(FileNotFoundException excep){
			System.err.println("Error: Unable to create the file");
			exit(1);
		}
		catch(IOException excep){
			System.err.println("Error: Unable to create the file");
			exit(1);
		}
		int wordcount = wordCount(in);

		try{
		in = new Scanner(new File(args[0]));
		}
		catch(FileNotFoundException excep){
			System.err.println("Error: Unable to create the file");
			exit(1);
		}
		String[] arr = read(in, wordcount);
		List list = insertionSort(arr);
		for(list.moveFront();list.index() >= 0; list.moveNext()){
			write.print(arr[list.get()]+" ");
		}
		write.close();
		in.close();
	}
}
