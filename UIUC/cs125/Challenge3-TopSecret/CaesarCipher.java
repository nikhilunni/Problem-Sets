//UIUC CS125 FALL 2013 MP. File: CaesarCipher.java, CS125 Project: Challenge3-TopSecret, Version: 2013-09-21T11:54:26-0500.431586818
/**
 * A program to search for to encrypt and decrypt lines of text. See
 * CaesarCipher.txt
 * Hints: line.charAt( int ) is useful.
 * You'll need loops, and conditions and variables
 * You'll need to read the Test cases to understand how your program should work.
 * Good Programming Hints: "DRY: Don't Repeat Yourself"
 * Try to make your program as short as possible.
 * TODO: add your netid to the line below
 * @author nunni2
 */
public class CaesarCipher {

	
	private static String offsetString(String input, int offset)
	{
		char[] output = new char[input.length()];
		char[] charInput = input.toCharArray();
		for(int i = 0; i < input.length(); i++) {
			output[i] = (char)(charInput[i]);
			if(output[i] >= 65 && output[i] <= 90) {
				output[i] += offset;
				if(output[i] > 90) {
					output[i] -= 26;
				}
				if(output[i] < 65) {
					output[i] += 26;
				}
			}

		}
		return new String(output);
	}
	
	private static String secretOffset(String input, int sign) {
		char[] output = new char[input.length()];
		char[] charInput = input.toCharArray();
		for(int i = 0; i < input.length(); i++) {
			output[i] = (char)(charInput[i]);
			if(output[i] >= 65 && output[i] <= 90) {
				int temp = i;
				while(temp >= 26)
					temp -= 26;
				while(temp <= 0)
					temp += 26;
				output[i] += temp * sign;
				if(output[i] > 90) {
					output[i] -= 26;
				}
				if(output[i] < 65) {
					output[i] += 26;
				}
			}
			
		}		
		return new String(output);
	}
	public static void main(String[] strings) {
		boolean passed = false;
		boolean secret = false;
		int sign = 1;
		
		int offset = 0;
		while(!passed) {
			TextIO.putln("Please enter the shift value (between -25..-1 and 1..25)");
			offset = TextIO.getlnInt();
			if((offset >= 1 && offset <= 25) || (offset <= -1 && offset >= -25) ) {
				passed = true;
			}
			else {
				if(offset == 999) {
					secret = true;
					passed = true;
				}
				else if(offset == -999) {
					secret = true;
					passed = true;
					sign = -1;
				}
				else {
					TextIO.putln(offset + " is not a valid shift value.");
				}
			}
		}
		if(!secret) {
			TextIO.putln("Using shift value of " + offset);
		}
		else {
			TextIO.putln("Using position shift");
		}
		
		
		passed = false;
		
		while(!passed) {
			TextIO.putln("Please enter the source text (empty line to quit)");
			String text = TextIO.getln();
			if(text.isEmpty()) {
				passed = true;
			}
			else {
				TextIO.putln("Source   :" + text);
				if(!secret) {
					TextIO.putln("Processed:" + offsetString(text.toUpperCase(), offset));
				}
				else {
					TextIO.putln("Processed:" + secretOffset(text.toUpperCase(), sign));
				}
				
			}
		}
		TextIO.putln("Bye.");
		
	}

}
