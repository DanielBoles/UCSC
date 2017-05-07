//-----------------------------------------------------------------------------
// Queue.java
// implements the Queue ADT
// Author: Daniel Boles
// Project: pa4
//-----------------------------------------------------------------------------



public class Queue implements QueueInterface{
	
	private class Node{
		Object item;
		Node next;

		Node(Object item){
			this.item = item;
			next = null;
		}
	}

	private Node head;
	private int itemCount;

	public Queue(){
		head = null;
		itemCount = 0;
	}

	public boolean isEmpty(){
		if (itemCount == 0){
			return true;
		}
		return false;
	}
	
	public int length(){
		return itemCount;
	}


   public void enqueue(Object newItem){
   		if (head == null){
   			head = new Node(newItem);
   		}
   		else{
   			Node hold = head;
   			while(hold.next != null){
   				hold = hold.next;
   			}
   			hold.next = new Node(newItem);
   		}
   		itemCount++;
   }

   public Object dequeue() throws QueueEmptyException{
   		if (head == null){
   			throw new QueueEmptyException("dequeue() cannot remove from an empty Queue");
   		}
   		Node hold = head;
   		head = hold.next;
   		itemCount--;
   		return hold.item;
   }

   public Object peek() throws QueueEmptyException{
   		if (head == null){
   			throw new QueueEmptyException("peek() cannot view an empty Queue");
   		}
   		else{
   			return head.item;
   		}
   }

   public void dequeueAll() throws QueueEmptyException{
   		if (head == null){
   			throw new QueueEmptyException("dequeue() cannot remove from an empty Queue");
   		}
   		head = null;
   		itemCount = 0;
   }
   public String toString(){
   		String queueString = "";
   		Node hold = head;
   		while(hold != null){
   			queueString += hold.item + " ";
   			hold = hold.next;
   		}
   		return queueString;
   }
}
