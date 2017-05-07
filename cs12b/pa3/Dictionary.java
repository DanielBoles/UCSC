/* Author: Daniel Boles
 * Project: PA3
 * Class: 12b
 */

import java.io.*;
import java.util.Scanner;

public class Dictionary implements DictionaryInterface{ 

   private class Node { 
       String key; 
       String value; 
       Node next; 
 
       Node (String key, String value) { 
          this.key = key; 
          this.value = value; 
          next = null; 
       } 
   } 


private Node head;
private int itemCount;

public Dictionary(){
   head = null;
   itemCount = 0;
}

   // isEmpty()
   // pre: none
   // returns true if this Dictionary is empty, false otherwise
   public boolean isEmpty(){
      if(itemCount != 0){
         return false;
      }
      return true;
   }

   // size()
   // pre: none
   // returns the number of entries in this Dictionary
   public int size(){
      return itemCount;
   }

   private Node findKey(String key){
      Node H = head;
      if(H == head){
         while(H != null){
            if(H.key != key){
               H = H.next;
            }
            else{
               return H;
            }
         }
      }
   return null;
      
   }

   // lookup()
   // pre: none
   // returns value associated key, or null reference if no such key exists
   public String lookup(String key){
      if(findKey(key) != null){
         Node H = findKey(key);
         return H.value;
      }
      else{
         return null;
      }


   }

   // insert()
   // inserts new (key,value) pair into this Dictionary
   // pre: lookup(key)==null
   public void insert(String key, String value) throws DuplicateKeyException{
      if(findKey(key) != null){
         throw new DuplicateKeyException("cannot insert duplicate keys");
      }
      else{
         if(head == null){
            Node H = new Node(key, value);
            head = H;
         }
         else{
            Node H = head;
            while(H.next != null){
               H = H.next;
            }
            H.next = new Node(key, value);
         }
         itemCount++;
      }
   }

   // delete()
   // deletes pair with the given key
   // pre: lookup(key)!=null
   public void delete(String key) throws KeyNotFoundException{
      if(findKey(key) == null){
         throw new KeyNotFoundException("cannot delete non-existent key");
      }
      else{
         if(itemCount == 1){
            head = null;
         }
         else{
            Node H = head;
            if(H == findKey(key)){
               head = H.next;
            }else{
               while(H.next != findKey(key)){
                  H = H.next;
                  }
               H.next = H.next.next;
            }   
         }
         itemCount--;
      }
   }

   // makeEmpty()
   // pre: none
   public void makeEmpty(){
      head = null;
      itemCount = 0;
   }

   // toString()
   // returns a String representation of this Dictionary
   // overrides Object's toString() method
   // pre: none
   public String toString(){
      String string = "";
      Node H = head;
      while(H != null){
         string = string + H.key + " " + H.value + "\n";
         H = H.next;
      } 
      return string;     
   }
}