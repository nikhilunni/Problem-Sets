//UIUC CS125 FALL 2013 MP. File: ExampleIf.java, CS125 Project: Challenge3-TopSecret, Version: 2013-09-21T11:54:26-0500.431586818
public class ExampleIf {

	public static void main(String[] args) {
		TextIO.putln("By reading this source code carefully you can work what you need");
		TextIO.putln("to type to make this program print \"Congratulations!\"");
		int value = 0;
		int count = 0;
		while (value < 5 || value > 20) {
			if (count > 0)
				TextIO.putln("Try again");
			TextIO.putln("Enter an integer b	etween 5 and 20 inclusive");
			value = TextIO.getlnInt();
			count++;
		}
		if (count > 3) {
			TextIO.putln("You needed " + count + " tries to follow simple instructions");
		} else {
			if (value > 10)
				TextIO.putln("Why so large?");
			else {
				value = 10;
			}
		}
		TextIO.putln("Value = "+value);
		if (value < 10)
			TextIO.putln("Congratulations!");
		else TextIO.putln("Read the source code carefully, figure it out and run me again!");
	}

}
