//UIUC CS125 FALL 2013 MP. File: MyScriptPrinter.java, CS125 Project: Challenge2-Hollywood, Version: 2013-09-17T09:52:07-0500.008393307
/**
 * A program to print one actor's lines. 
 * See ScriptPrinter.txt for more information.
 * TODO: add your netid to the line below
 * @author nunni2
 */
public class MyScriptPrinter {
	/**
	 * @param args
	 */
	public static void main(String[] args) {

		boolean output=false; //Set to true when we find the desired character
		String name=""; // Only print lines for this character
		
		TextIO.putln("Which character's lines would you like? (NEO,MORPHEUS,ORACLE)");
		name = TextIO.getln().toUpperCase();

		TextIO.readFile("thematrix.txt"); // stop reading from the keyboard- use the script

		TextIO.putln(name + "'s lines:");
		
		output = false; // initially don't print anything

		// This loop will read one line at a time from the script until it
		// reaches the end of the file and then TextIO.eof() will return true.
		// eof means end-of-file
		while (false == TextIO.eof()) {
			String line = TextIO.getln(); // Read the next line
			if(line.length() == 0)
				output = false;

			if (output)
				TextIO.putln(name + ":\"" +line.trim() + "\""); // Only print the line if 'output' is true
			
			if (line.indexOf(name) >= 0)
				output = true; // We found the character's name, time to start printing their lines



		}
		System.out.println("---");
	}

}
