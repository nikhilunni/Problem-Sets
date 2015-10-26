//UIUC CS125 FALL 2013 MP. File: Factorial.java, CS125 Project: Challenge1-DebugMe, Version: 2013-09-10T09:56:29-0500.044586399

/**
 * A program to calculate a factorial. The given code may contain errors. Fix the
 * given code and add additional code to calculate a factorial and pass the unit
 * tests. Hint sometimes an 'int' just 'aint big enough.
 * 
 * @see Factorial-ReadMe.txt for details on how to complete this program.
 * @author nunni2
 */
public class Factorial {
	public static void main(String[] args) {
		int max = 0;
		
		boolean inputBad = true;
		while(inputBad)
		{
			System.out.println("Enter a number between 1 and 20 inclusive.");
			max = TextIO.getlnInt();
			int num = max;

			if(max >= 1 && max <= 20)
			{
				inputBad = !inputBad;
				long multiple = 1;
				while(max > 1) {
					multiple = multiple * max;
					max--;
				}
				TextIO.putln(num + "! = " + multiple);
			}
		}

	}
}
