//-----------------------------------------------------------------------------
// Simulation.java
// Author: Daniel Boles
// Project: pa4
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Simulation{

	public static void main(String[] args) throws IOException{

	//    1.  check command line arguments
	//
	//    2.  open files for reading and writing
	//
	//    3.  read in m jobs from input file
	//
	//    4.  run simulation with n processors for n=1 to n=m-1  {
	//
	//    5.      declare and initialize an array of n processor Queues and any 
	//            necessary storage Queues
	//
	//    6.      while unprocessed jobs remain  {
	//
	//    7.          determine the time of the next arrival or finish event and 
	//                update time
	//
	//    8.          complete all processes finishing now
		/*		
		*/
	//
	//    9.          if there are any jobs arriving now, assign them to a processor 
	//                Queue of minimum length and with lowest index in the queue array.
		/*				if(inputQ.peek().arrTime == time){
							int shortest = getShorterstQ(jobs);
							jobs[shortest].enque(inputQ.dequeue())}
							//ipdate finish time
		*/

	
	//    10.     } end loop
	//
	//    11.     compute the total wait, maximum wait, and average wait for 
	//            all Jobs, then reset finish times
	//
	//    12. } end loop
	//
	//    13. close input and output files

		// Begin declaring + initializing variables and queues
		Queue StorageA = new Queue();
		Queue StorageB = new Queue();
		Queue Finish = new Queue();
		Queue[] processorQueues = null;
		Scanner scan = null;
		PrintWriter rpt = null;
		PrintWriter trc = null;
		int m = 0;
		int n = 0;
		int i = 0;
		int time = 0;
		int totalWait, maxWait;
		double averageWait;
		int processors;
		Job j = null;

		// input check
		if(args.length != 1) {
			System.exit(1);
		}

		// create files and begin the code
		scan = new Scanner(new File(args[0]));
		rpt = new PrintWriter(new FileWriter(args[0] + ".rpt"));
		trc = new PrintWriter(new FileWriter(args[0] + ".trc"));
		m = jobCount(scan);
		while(scan.hasNextLine()){
			j = getJob(scan);
			StorageA.enqueue(j);
		}

		// output formatting
		trc.println("Trace File: " + (args[0] + ".trc"));
		trc.println(m + " Jobs: ");
		trc.println(StorageA.toString() + "\n");

		rpt.println("Report file: " + (args[0] + ".rpt"));
		rpt.println(m + "Jobs:");
		rpt.println(StorageA.toString() + "\n");
		rpt.println("***********************************************************");

		for(n = 1; n < m; n++){

			// set initial values
			averageWait = 0.00;
			maxWait = 0;
			totalWait = 0;

			for(i = 1; i < StorageA.length() + 1; i++){
				j = (Job)StorageA.dequeue();
				j.resetFinishTime();
				StorageB.enqueue(j);
				StorageA.enqueue(j);
			}
			processors = n;
			processorQueues = new Queue[n + 2];
			processorQueues[0] = StorageB;
			processorQueues[n+1] = Finish;

			for (i = 1; i < processors + 1; i++){
				processorQueues[i] = new Queue();
			}
			// More output formatting
			trc.println("*****************************");
			if(processors != 1){
				trc.println(processors + "processors:");
			}
			else{
				trc.println(processors + "processor:");
			}
			trc.println("*****************************");
			
			trc.println("time = " + time);
			trc.println("0: " + StorageB.toString());
			for(i = 1; i < processors + 1; i++){
				trc.println(i + ": " + processorQueues[i]);
			}

			while(Finish.length() != m){
				
				//initialiing variables used in indexing the processing as well as
				//variables used in determining time count.
				int finalIndex = 1;
				int tempIndex = 1;
				int comp = -1;
				int length = -1;
				int finalLength = -1;
				int temporaryWait = 0;
				int compFinal = Integer.MAX_VALUE;
				Job compare = null;
				int finishtime;

				// begin processing
				if(StorageB.isEmpty() == false){
					compare = (Job)StorageB.peek();
					compFinal = compare.getArrival();
					finalIndex = 0;
				}
				for(i = 1; i < processors + 1; i++){
					if(processorQueues[i].length() != 0){
						compare = (Job)processorQueues[i].peek();
						comp = compare.getFinish();
					}
					if(comp < compFinal && comp != -1){
						compFinal = comp;
						finalIndex = i;
					}
					time = compFinal;
				}
				if(finalIndex == 0){
					tempIndex = 1;
					finalLength = processorQueues[tempIndex].length();
					for(i = 1; i < processors + 1; i++){
						length = processorQueues[i].length();
						if(length < finalLength){
							tempIndex = i;
							finalLength = length;
						}
					}
					compare = (Job)StorageB.dequeue();
					processorQueues[tempIndex].enqueue(compare);
					
					if(processorQueues[tempIndex].length() == 1){
						compare = (Job)processorQueues[tempIndex].peek();
						compare.computeFinishTime(time);
					}
				}
				else{
					compare = (Job)processorQueues[finalIndex].dequeue();
					Finish.enqueue(compare);
					//compare.computeFinishTime(time);
					temporaryWait = compare.getWaitTime();
					if(temporaryWait > maxWait){
						maxWait = temporaryWait;
					}
					totalWait += temporaryWait;
					if(processorQueues[finalIndex].length()>= 1){
						compare = (Job)processorQueues[finalIndex].peek();
						compare.computeFinishTime(time);
					}
				}

				// Print the time followed by the queue to be processed, then
				// print the queue that has been processed.
				trc.println("\n time=" + time);
				trc.println("0: " + StorageB.toString() + processorQueues[n+1]);
				for(i = 1; i < processors+1; i++){
					trc.println(i + ": " + processorQueues[i]);
				}
			}

			averageWait = ((double) totalWait/m);
			averageWait = (double)Math.round(averageWait*100)/100;
			trc.println();

			//formatting
			if (processors != 1){
				rpt.println(processors + " processors: totalWait=" + totalWait + ", maxWait=" + maxWait + ", averageWait=" + averageWait);
			}
			else{
				rpt.println(processors + " processor: totalWait=" + totalWait + ", maxWait=" + maxWait + ", averageWait=" + averageWait);
			}
			time = 0;
			Finish.dequeueAll();
		}

		// close files
		scan.close();
		rpt.close();
		trc.close();
	}
	// get job function provided
	public static Job getJob(Scanner in) {
	      String[] s = in.nextLine().split(" ");
	      int a = Integer.parseInt(s[0]);
	      int d = Integer.parseInt(s[1]);
	      return new Job(a, d);
   }
   // jobCount helper function to return how many jobs are passed in
   public static int jobCount(Scanner scan){
   		String s = scan.nextLine();
   		int x = Integer.parseInt(s);
   		return x;
   }

}