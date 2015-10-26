//UIUC CS125 FALL 2013 MP. File: OddSum.java, CS125 Project: Challenge3-TopSecret, Version: 2013-09-21T11:54:26-0500.431586818
/**
 * Prints sum of odd numbers in a specific format.
 * TODO: add your netid to the line below
 * @author nunni2
 */
public class OddSum { 
/**
Example output if user enters 10:
Max?
1 + 3 + 5 + 7 + 9 = 25
25 = 9 + 7 + 5 + 3 + 1

Example output if user enters 11:
Max?
1 + 3 + 5 + 7 + 9 + 11 = 36
36 = 11 + 9 + 7 + 5 + 3 + 1

 */
 public static void main(String[] args) { 
	 TextIO.putln("Max?");
	 int num = TextIO.getlnInt();
	 int sum = 0;

	 for(int i = 1; i < (num % 2 == 0 ? num-2:num-1); i+=2) {
		 TextIO.put(i + " + ");
		 sum += i;
	 }
	 sum += num % 2 == 0 ? num-1:num;
	 TextIO.put((num % 2 == 0 ? num-1:num) + " = " + sum + "\n");

	 TextIO.put(sum + " = ");
	 for(int i = (num % 2 == 0 ? num-1:num); i > 2; i-=2) {
		 TextIO.put(i + " + "); 
	 }
	 TextIO.putln("1");
		
	
  } // end of main method
} // end of class 
