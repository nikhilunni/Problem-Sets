//UIUC CS125 FALL 2013 MP. File: InsecureCombinationLockBreaker.java, CS125 Project: Challenge7-RecursiveKnight, Version: 2013-11-12T10:38:50-0600.575917765
/*
 * @author nunni2
 */
public class InsecureCombinationLockBreaker {

	public static int breakLock(InsecureCombinationLock lock) {
		// Write your code here to break the combination lock
		// Read the combination lock source code to determine
		// the weakness in the lock
		
		// You do not need to use recursion.

		// - An inside programmer has written some extra
		// code that gives you a tiny hint about how close you
		// are to opening the lock.
		// Using this single bit of information, your job
		// is to find the integer value that opens the lock
		
		// This method is only for honors students and the curious to complete
		// Honor students: Be prepared to demonstrate how you completed
		// this problem!

		// **** This method is not graded as part of the MP ****
		
		// (but for your own local testing just remove 
		// the 'xxx's in the test  method in InsecureTest.java)
		
		// Beginner: This problem is not for beginners
		
		// Intermediate: It took me 90 minutes to create a robust solution 
		// (including 15 minutes debugging it with several million tests).
		
		// Advanced: 'Don't be wasteful' -
		// Assume there is a 1s time penalty for every unlocking attempt,
		// make sure your code uses the fewest number of unlocking attempts
		// ie. It will open the lock as quickly as possible.
		// (My solution was little wasteful but was simpler to implement).
		
		return 42;
	}

	public static void main(String[] args) {
			InsecureCombinationLock lock = new InsecureCombinationLock();
			int code = breakLock(lock);
			
			System.out.println("Unlock code:"+code);
			System.out.println(lock.isUnlocked() ? "Unlocked :-)" : "Still Locked :-(");
	}
}
