//UIUC CS125 FALL 2013 MP. File: CallAStaticMethod.java, CS125 Project: Challenge5-DataStructures, Version: 2013-10-14T15:32:35-0500.796362776
/**
 * Prints out only lines that contain an email address Each printed line is
 * justified to right by prepending the text with '.' characters The minimum
 * width of the line including padding is 40 characters. See the test case for
 * example input and expected output.
 * @author nunni2
 */
class CallAStaticMethod {

	public static void main(String[] args) {		
		while (!TextIO.eof()) {			
			String line = TextIO.getln();
			if(ExampleClassMethods.isEmailAddress(line)) {
				if(line.length() < 40)
					TextIO.put(ExampleClassMethods.createPadding('.', 40-line.length()));
				TextIO.putln(line);
			}
		}

	}
}
