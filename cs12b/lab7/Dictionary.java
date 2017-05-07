//-----------------------------------------------------------------------------
// Dictionary.java
// Author: Daniel Boles
// Project: lab7
//-----------------------------------------------------------------------------


import java.io.*;
import java.util.Scanner;

public class Dictionary implements DictionaryInterface{
	private class Node{
		Dict item;
		Node right;
		Node left;

		Node(Dict itm){
			item = itm;
			right = null;
			left = null;
		}
	}

	private Node head;
	private int itemCount;

	private class Dict { 
		String key;
		String value;

		Dict(String k, String v){
			key = k;
			value = v;
		}
	}

	public Dictionary(){
		head = null;
		itemCount = 0;
	}

	private Node findKey(Node R, String k){
		if(R == null || R.item.key.equals(k)){
			return R;
		}
		if(R.item.key.compareToIgnoreCase(k) > 0){
			return findKey(R.left, k);
		}
		else{
			return findKey(R.right, k);
		}
	}

	Node findParent(Node N, Node R){
		if(R != null){
			Node P = null;
			if(N != R){
				P = R;
				while(P.left != N && P.right != N){
					if(N.item.key.compareToIgnoreCase(P.item.key) > 0){
						P = P.right;
					}
					else{
						P = P.left;
					}
					
				}
			}
			return P;
		}
		return null;
	}

	Node findLeftmost(Node R){
		Node L = R;
		if(L != null){
			for(;L.left != null; L = L.left);	
			return L;		
		}
		return null;
	}

	void printInOrder(Node R){
		if(R != null){
			printInOrder(R.left);
			System.out.println(R.item.key + " " + R.item.value);
			printInOrder(R.right);
		}
	}

	void deleteAll(Node N){
		if(N != null){
			deleteAll(N.left);
			deleteAll(N.right);
		}
	}

	public boolean isEmpty(){
		if(itemCount ==0){
			return true;
		}
		return false;
	}

	public int size(){
		return itemCount;
	}

	public String lookup(String key){
		Node N;
		N = findKey(head, key);
		if(N == null){
			return null;
		}
		return N.item.value;
	}

	public void insert(String key, String value) throws DuplicateKeyException{
		Node N, A, B;
		if(findKey(head, key) != null){
			throw new DuplicateKeyException("Dictionary Error: cannot insert() duplicate key");
		}
		B = null;
		A = head;
		N = new Node(new Dict(key, value));
		while(A != null){
			B = A;
			if(A.item.key.compareToIgnoreCase(key) > 0){
				A = A.left;
			}
			else{
				A = A.right;
			}
		}
		if(B == null){
			head = N;
		}
		else if(B.item.key.compareToIgnoreCase(key) > 0){
			B.left = N;
		}
		else{
			B.right = N;
		}
		itemCount++;
	}

	public void delete(String key) throws KeyNotFoundException{
		Node N, P, S;
		if(findKey(head, key) == null){
			throw new KeyNotFoundException("Dictionary Error: delete() cannot delete non-existent key");
		}
		N = findKey(head, key);
		if(N.left == null && N.right == null){
			if(N == head){
				head = null;
			}
			else{
				P =findParent(N, head);
				if(P.right == N){
					P.right = null;
				}
				else{
					P.left = null;
				}
			}
		}
		else if(N.right == null){
			if(N == head){
				head = N.left;
			}
			else{
				P = findParent(N, head);
				if(P.right == N){
					P.right = N.left;
				}
				else{
					P.left = N.left;
				}
			}
		}
		else if(N.left == null){
			if(N == head){
				head = N.right;
			}
			else{
				P = findParent(N, head);
				if(P.right == N){
					P.right = N.right;
				}
				else{
					P.left = N.right;
				}
			}
		}
		else{
			S = findLeftmost(N.right);
			N.item.key = S.item.key;
			N.item.value = S.item.value;
			P = findParent(S, N);
			if(P.right == S){
				P.right = S.right;
			}
			else{
				P.left = S.right;
			}
		}
		itemCount--;
	}

	public void makeEmpty(){
		deleteAll(head);
		head = null;
		itemCount = 0;
	}

	public String toString(){
		printInOrder(head);
		return "";
	}

}