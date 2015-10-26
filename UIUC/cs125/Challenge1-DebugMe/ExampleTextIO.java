//UIUC CS125 FALL 2013 MP. File: ExampleTextIO.java, CS125 Project: Challenge1-DebugMe, Version: 2013-09-10T09:56:29-0500.044586399


public class ExampleTextIO {

	/**
	 * Hint: You'll need to use Scanner for Turings Craft  
	 * because TextIO is not part of the standard Java classes.
	 */
	public static void main(String[] args) {
		// Using TextIO to print output and get input is simple
		// and recommended for the MPs!
		TextIO.putln("Enter three unique integer values.");
		
		int a = TextIO.getlnInt();
		int b = TextIO.getlnInt();
		int c = TextIO.getlnInt();
		
		if(a>b && b>c) TextIO.putln("You entered three integers in decreasing order.");
		if(a==b && b==c) TextIO.putln("You entered three integers that are the same!");
		if(a==42 || b==42 || c==42) TextIO.putln("The answer to life, the universe and everything.");

	}

}
