/* Author: Daniel Boles
 * Project: PA3
 * Class: 12b
 */

public class DictionaryTest{

   public static void main(String[] args){
      String v;
      Dictionary A = new Dictionary();

      System.out.println(A.isEmpty());
      System.out.println(A.size());
      A.insert("1", "1");
      A.insert("2", "Q");
      System.out.println(A);

      v = A.lookup("1");
      System.out.println("key=1 "+(v==null?"not found":("value="+v)));
      v = A.lookup("3");
      System.out.println("key=3 "+(v==null?"not found":("value="+v)));

      A.insert("2","Q");  // causes DuplicateKeyException

      System.out.println(A.isEmpty());
      System.out.println(A.size());
      A.delete("1");
      System.out.println(A);

      A.delete("5");  // causes KeyNotFoundException

      A.makeEmpty();
      System.out.println(A.isEmpty());
      System.out.println(A);

   }
}
