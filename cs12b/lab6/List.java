//-----------------------------------------------------------------------------
// List.java
// implements the List ADT interface
// Author: Daniel Boles
// Project: lab6
//-----------------------------------------------------------------------------


@SuppressWarnings("overrides")

public class List<T> implements ListInterface<T>{

	private class Node{
		T item;
		Node next;

		Node(T itm){
			item = itm;
			next = null;
		}
	}

	private Node head;
	private int itemCount;

	public List(){
		head = null;
		itemCount = 0;
	}

	public boolean isEmpty(){
		return(itemCount==0);
	}

	public int size(){
		return itemCount;
	}

	public Node search(int index){
		Node X = head;
		for(int i = 1; i < index; i++, X = X.next);
		return X;
	}

	public T get(int index) throws ListIndexOutOfBoundsException{
		if(index < 1 || index > itemCount){
			throw new ListIndexOutOfBoundsException("get(): " + index + " is not a valid input index.");
		}
		Node X = search(index);
		return X.item;
	}

	public void add(int index, T newItem) throws ListIndexOutOfBoundsException{
		if(index < 1 || index > itemCount+1){
			throw new ListIndexOutOfBoundsException("add(): " + index + " is not a valid input index.");
		}
		if(index == 1) {
			Node X = new Node(newItem);
			X.next = head;
			head = X;
		}
		else{
			Node Y = search(index-1);
			Node Z = Y.next;
			Node X = new Node(newItem);
			Y.next = X;
			X.next = Z;
		}
		itemCount++;
	}

   public void remove(int index) throws ListIndexOutOfBoundsException{
   		if(index < 1 || index > itemCount){
			throw new ListIndexOutOfBoundsException("remove(): " + index + " is not a valid input index.");
		}
		if(index == 1){
			head = head.next;
		}
		else{
			Node X = search(index-1);
			X.next = X.next.next;
		}
		itemCount--;
   	}

   	public void removeAll(){
   		head = null;
   		itemCount = 0;
   	}
 	public String toString(){
 		String ListString = "";
 		for(Node X = head; X != null; X = X.next){
 			ListString += X.item.toString() + " ";
 		}
 		return ListString;
 	}

   @SuppressWarnings("unchecked") 
   public boolean equals(Object rhs){
       	boolean eq = false; 
      	List<T> R = null;
      	Node X = null;
      	Node Y = null;
        if(this.getClass()==rhs.getClass()){
            R = (List<T>) rhs;      
   			eq = (this.itemCount == R.itemCount);
   			X = this.head;
   			Y = R.head; 
   			while(eq && X != null){
   				eq = (X.item == Y.item);
   				X = X.next;
   				Y = Y.next;
   			}   
   		}    
   		return eq; 
   	}
} 

	   