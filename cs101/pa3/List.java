/*
 * List.java
 * Daniel Boles
 * dawboles
 * pa3
 * description: This is a doubly linked list ADT. This consists of a nodes 
 * which point forward and backward and creates a chain of elements.
 * This List now implements objects.
 *
*/

class List{
	private class node{
		Object item;
		node next;
		node prev;

		node Node(Object itm){
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
	public Object front(){
		if(this.length() > 0){
			return head.item;
		}
		else{
			System.out.println("Cannot find first element of an empty list.");
			throw new RuntimeException();
		}
	}
	public Object back(){
		if(this.length() > 0){
			return tail.item;
		}
		else{
			System.out.println("Cannot find last element of an empty list.");
			throw new RuntimeException();
		}

	}
	public Object get(){
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
	public void prepend(Object data){
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
	public void append(Object data){
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
	public void insertBefore(Object data){
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
	public void insertAfter(Object data){
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
    public boolean equals(Object L){
		node right = head;
		node left = ((List)L).head;
		while(right != null && left != null){
			if(!(right.item.equals(left.item))){
				return false;
			}
			right = right.next;
			left = left.next;
		}
		if(right != null || left != null){
			return false;
		}
		return true;
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
	
}
