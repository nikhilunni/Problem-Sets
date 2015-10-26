//UIUC CS125 FALL 2013 MP. File: InsecurePasswordLockBreaker.java, CS125 Project: Challenge7-RecursiveKnight, Version: 2013-11-12T10:38:50-0600.575917765
/*
 * @author nunni2
 */
public class InsecurePasswordLockBreaker {

	public static char[] breakLock(InsecurePasswordLock lock) {
		int length = 0;
		while(lock.open(new char[length]) < 0)
			length++;
		char[] key = new char[length];
		
		int i = 0;
		while(i < length) {
			key[i] = (char) ('A' + (int) (26 * Math.random()));
			if(lock.open(key) > i)
				i++;
		}
			
		// write code here to determine the secret password
		// to unlock the given lock object.
		// You do not need to use recursion.
		// Hint: Read the source code of InsecurePasswordLock
		// The lock has a weakness....
		// Understand it and you can write an algorithm to quickly find the
		// secret password
		// (A brute force guess of a 40 character password would take a long
		// time...
		// as there are 26^40 combinations!
		// Your method should find it in a few seconds.

		// Beginner: You should complete this code in less than an hour

		// Advanced Code-Golf: Can you complete this method in 8 lines
		// (excluding the top and bottom given
		// lines and after autoformating your code)
		
		// Crazy Instructor level:
		// I can write a complete albeit-inefficient solution using single while loop :-)
		// expression: while (____){/*NoCodeHere*/}
		return key;
	}

	public static void main(String[] args) {
		InsecurePasswordLock lock = new InsecurePasswordLock();
		char[] key = breakLock(lock);
		System.out.println(key);
		System.out.println(lock.isUnlocked());
	}
}
