//UIUC CS125 FALL 2013 MP. File: MovieSurvey.java, CS125 Project: Challenge2-Hollywood, Version: 2013-09-17T09:52:07-0500.008393307
/**
 * A program to run a simple survey and report the results. See MovieSurvey.txt
 * for more information. TODO: add your netid to the line below
 * 
 * @author nunni2
 */
public class MovieSurvey {
	public static void main(String[] arg) {
		TextIO.putln("Welcome. We're interested in how people are watching movies this year.\n"+
							"Thanks for your time. - The WRITERS GUILD OF AMERICA.\n" +
							"Please tell us about how you've watched movies in the last month.");
		
		TextIO.putln("How many movies have you seen at the cinema?");
		int cinema = TextIO.getlnInt();
		TextIO.putln("How many movies have you seen using a DVD or VHS player?");
		int dvd = TextIO.getlnInt();
		TextIO.putln("How many movies have you seen using a Computer?");
		int computer = TextIO.getlnInt();
		
		TextIO.putln("Summary: " + cinema + " Cinema movies, " + dvd + " DVD/VHS movies, " 
					+ computer + " Computer movies");
		TextIO.putln("Total: " + (cinema+dvd+computer) + " movies");
		TextIO.put("Fraction of movies seen at a cinema: ");
		TextIO.putf("%.2f", 100 * cinema/(float)(cinema+dvd+computer)); TextIO.putln("%");
		TextIO.put("Fraction of movies seen outside of a cinema: ");
		TextIO.putf("%.2f",100 * (1 - cinema/(float)(cinema+dvd+computer))); TextIO.putln("%");
		
		
		
		// TODO: Write your program here
		// Hints :
		// Formatted output
		// http://math.hws.edu/javanotes/c2/s4.html#basics.4.4
		
		// Don't just copy paste the expected output
		// For grading purposes your code may be tested
		// with other input values.
	}
}
