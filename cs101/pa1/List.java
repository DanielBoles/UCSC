/*
 * List.java
 * Daniel Boles
 * dawboles
 * pa1
 * description: This is a doubly linked list ADT. This consists of a node which points
 * forward and backward and creates a chain of elements 
 *
*/

class List{
	private class node{
		int item;
		node next;
		node prev;

		public node Node(int itm){
			node newNode = new node();
			newNode.item = itm;
			newNode.next = null;
			newNode.prev = null;
			return newNode;
		}
		public String toString(){
			String data = String.valueOf(this.item);
			return data;
		}
	}
	private node head;
	private node tail;
	private int length;
	private node cursorNode = null;
	private int cursor = -1;


	public void List(){
		List newList = new List();
	}
	public boolean isEmpty(){
		return(this.length() == 0);
	}
	public int length(){
		return length;
	}
	
	public void clear(){
		cursor = -1;
		cursorNode = null;
		head = null;
		tail = null;
		length = 0;
	}
	public int index(){
		return cursor;
	}
	public int front(){
		if(this.length() > 0){
			return head.item;
		}
		else{
			System.out.println("Cannot find first element of an empty list.");
			throw new RuntimeException();
		}
	}
	public int back(){
		if(this.length() > 0){
			return tail.item;
		}
		else{
			System.out.println("Cannot find last element of an empty list.");
			throw new RuntimeException();
		}

	}
	public int get(){
		if(isEmpty()){
			System.out.println("Cannot find element of an empty list.");
			throw new RuntimeException();
		}
		if(cursor<0){
			System.out.println("Cursor is not on list.");
			throw new RuntimeException();
		}
		return this.cursorNode.item;
	}
	public void moveFront(){
		if(isEmpty()){
			System.out.println("Cannot move to head element of an empty list.");
			throw new RuntimeException();
		}
		cursorNode = this.head;
		cursor = 0;
		return;
	}
	public void moveBack(){
		if(isEmpty()){
			System.out.println("Cannot move to tail element of an empty list.");
			throw new RuntimeException();
		}
		cursorNode = this.tail;
		cursor = this.length()-1;
		return;
	}
	public void movePrev(){
		if(cursorNode == head){
			this.cursor = -1;
		}
		else if(cursor > 0 && cursor <= length()-1){
			cursorNode = cursorNode.prev;
			this.cursor--;
		}
		return;
	}
	public void moveNext(){
		if(cursorNode == tail){
			this.cursor = -1;
		}else if(cursor >= 0 && cursor < this.length()-1){
			cursorNode = cursorNode.next;
			this.cursor++;
		}
		return;
	}
	public void prepend(int data){
		node newNode = new node();
		newNode.item = data;
		if(isEmpty()){
			head = newNode;
			tail = newNode;
		}
		else{
			head.prev = newNode;
			newNode.next = head;
			head = newNode;
		}
		length++;
	}
	public void append(int data){
		node newNode = new node();
		newNode.item = data;
		if(isEmpty()){
			head = newNode;
			tail = newNode;
		}
		else{
			tail.next = newNode;
			newNode.prev = tail;
			tail = newNode;
		}
		length++;
	}
	public void insertBefore(int data){
		if(!(this.length() > 0 && cursor >= 0)){
			return;
		}
		node newNode = new node();
		newNode.item = data;
		newNode.next = cursorNode;
		newNode.prev = cursorNode.prev;
		if(cursorNode != head){
			cursorNode.prev.next = newNode;
		}
		cursorNode.prev = newNode;
		if(cursorNode == head){
			head = newNode;
		}
		length++;
	}
	public void insertAfter(int data){
        if(!(this.length() > 0 && cursor >= 0)){
                return;
        }
        node newNode = new node();
        newNode.item = data;
        newNode.prev = cursorNode;
        newNode.next = cursorNode.next;
        if(cursorNode != tail){
                cursorNode.next.prev = newNode;
        }
        cursorNode.next = newNode;
        if(cursorNode == tail){
                tail = newNode;
        }
        length++;
    }
    public boolean equals(List L){
		int i;
		int j;
		j=0;
		boolean result;
		result = true;
		int temp;
		temp = cursor;
		if(this.length() != L.length()){
			result = false;
		}
		this.moveFront();
		L.moveFront();
		for(i = 0; i<this.length(); i++){
			if(this.cursorNode.item != L.cursorNode.item){
				result = false;
			}
			this.moveNext();
			L.moveNext();
		}
		this.cursorNode = this.head;
		cursor = temp;
		while(j<cursor){
			cursorNode = cursorNode.next;
			j++;
		}
		return result;
	}
	public void deleteFront(){
		if(this.length() > 0){
			if(cursorNode == head){
				cursorNode = null;
			}
			head = head.next;
			head.prev = null;
			length--;
		}
	}
	public void deleteBack(){
		if(this.length() > 0){
            if(cursorNode == tail){
                cursorNode = null;
            }
            tail = tail.prev;
            tail.next = null;
            length--;
        }
    }
	public void delete(){
		if(cursorNode == head){
			deleteFront();
		}
		if(cursorNode == tail){
			deleteBack();
		}
		if(length() > 0 && cursor > 0){
			cursorNode.next.prev = cursorNode.prev;
			cursorNode.prev.next = cursorNode.next;
			length--;
			cursorNode = null;
		}
	}
	public String toString(){
		String result = "";
		node temp = head;
		while(temp != null){
			result += temp + " ";
			temp = temp.next;
		}
		return result;
	}
	public List copy(){
		List copy = new List();
		node temp = head;
		for(temp = head; temp != null; temp = temp.next){
			copy.append(temp.item);
		}
		return copy;
	}
	List concat(List L){
		List link = copy();
		node temp = head;
		for(temp = L.head; temp != null; temp = temp.next){
			link.append(temp.item);
		}
		return link;
	}
}
