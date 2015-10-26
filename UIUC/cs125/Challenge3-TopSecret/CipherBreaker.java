import java.util.HashMap;
import java.util.HashSet;

//UIUC CS125 FALL 2013 MP. File: CipherBreaker.java, CS125 Project: Challenge3-TopSecret, Version: 2013-09-21T11:54:26-0500.431586818
/**
 * See CipherBreaker.txt for instructions.
 * TODO: add your netid to the line below
 * 
 * @author nunni2
 */
public class CipherBreaker {

	public static void main(String[] args) {		
		HashSet<Character> punctuation = new HashSet<Character>();
		punctuation.add('\"'); 
		punctuation.add('-');
		punctuation.add('\'');
		punctuation.add('.');
		punctuation.add('!');
		punctuation.add(',');
		
		int[] alphabetCount = new int[26];
		int digits = 0;
		int spaces = 0;
		int puncts = 0;
		
		TextIO.putln("Text?");
		String line = TextIO.getln();
		TextIO.putln(line);	
		for(char c : line.toUpperCase().toCharArray()) {
			if(c >= 65 && c <= 91) {
				alphabetCount[c-65]++;
			}
			else if (c == 32)
			{
				spaces++;
			}
			else if (c >= 48 && c <= 57) {
				digits++;
			}
			else if (punctuation.contains(c)) {
				puncts++;
			}
			
		}
		for(int i = 0; i < 26; i++)
		{
			if(alphabetCount[i] > 0) {
				TextIO.putln((char)(i+65) + ":" + alphabetCount[i]);
			}			
		}
		if(digits > 0)
			TextIO.putln("DIGITS:" + digits);
		if(spaces > 0)
			TextIO.putln("SPACES:" + spaces);
		if(puncts > 0)
			TextIO.putln("PUNCTUATION:" + puncts);
		
		

}	}
