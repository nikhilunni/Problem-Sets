//UIUC CS125 FALL 2013 MP. File: Example_RecursivePrinter.java, CS125 Project: Challenge6-RecursionSee, Version: 2013-11-05T17:19:55-0600.019560079
public class Example_RecursivePrinter {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String message = "Hello!";
		printer(message);
	}

	private static void printer(String s) {
		if(s.length() ==0) {
			System.out.println(" ...Done!"); // Base case
			return;
		}
		// Try swapping the order of the next two lines
		
		System.out.print( s.charAt(0)+","); //First character

		printer(s.substring(1) ); // Recurse on remaining characters 
	}
	
}
