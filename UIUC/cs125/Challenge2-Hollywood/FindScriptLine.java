//UIUC CS125 FALL 2013 MP. File: FindScriptLine.java, CS125 Project: Challenge2-Hollywood, Version: 2013-09-17T09:52:07-0500.008393307
/**
 * A program to search for specific lines and print their line number.
 * See FindScriptLine.txt for more details
 * TODO: add your netid to the line below
 * @author nunni2
 */
public class FindScriptLine {

	public static void main(String[] args) {
		TextIO.putln("Please enter the word(s) to search for");
		String word = TextIO.getln();		
		TextIO.putln("Searching for '" + word + "'");
		TextIO.readFile("thematrix.txt");
		int lineNum = 1;
		while(!TextIO.eof())
		{
			String line = TextIO.getln();
			if(line.toLowerCase().contains(word.toLowerCase()))
			{
				TextIO.putln(lineNum + " - " + line.trim());
			}
			lineNum++;
		}
		TextIO.putln("Done Searching for '" + word + "'");
		
	}
}
