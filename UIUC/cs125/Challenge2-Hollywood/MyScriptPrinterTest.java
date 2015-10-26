//UIUC CS125 FALL 2013 MP. File: MyScriptPrinterTest.java, CS125 Project: Challenge2-Hollywood, Version: 2013-09-17T09:52:07-0500.008393307
import junit.framework.TestCase;

/**
* Tests ScriptPrinter. See ScriptPrinter.txt for more details.
* @author angrave
*
*/
public class MyScriptPrinterTest extends TestCase {
	String expected= "Which character's lines would you like? (NEO,MORPHEUS,ORACLE)\nNEO's lines:\nNEO:\"There is no spoon.  Right.\"\nNEO:\"Hello?\"\nNEO:\"Hello?\"\nNEO:\"You're the Oracle?\"\nNEO:\"Yeah.\"\nNEO:\"What vase?\"\nNEO:\"Sorry.\"\nNEO:\"How did you know...?\"\nNEO:\"Who?\"\nNEO:\"I think so.\"\nNEO:\"I don't know.\"\nNEO:\"What's the good news?\"\nNEO:\"Is that it, then?\"\nNEO:\"You do?\"\n---\n";

	public void testHeaderFooter() {
		CheckInputOutput.setInputCaptureOutput("NEO\n");
		MyScriptPrinter.main(new String[0]);
		int line = CheckInputOutput.checkCompleteOutput(expected);
		if(line>0) fail("Review incorrect output on line"+line);
	}
	public void testLineFormat() {
		CheckInputOutput.setInputCaptureOutput("ORACLE\n");
		MyScriptPrinter.main(new String[0]);
		boolean found = CheckInputOutput.checkOutputContains("ORACLE:\"No.  Here.\"");
		if(!found) fail("Output format is incorrect");
		
	}
	public void testLowercaseEntry() {
		CheckInputOutput.setInputCaptureOutput("neo\n");
		MyScriptPrinter.main(new String[0]);
		int line = CheckInputOutput.checkCompleteOutput(expected);
		if(line>0) fail("Review incorrect output on line"+line);
	}
	public void testAuthorship() {
		boolean success = CheckInputOutput.checkAuthorship("MyScriptPrinter.java");
		if(!success) fail("Fix @authorship");
	}
			
	public void tearDown() {
		CheckInputOutput.resetInputOutput();
	}
	public void setUp() throws Exception{
		CheckInputOutput.setUp();
			super.setUp();
	}
}
