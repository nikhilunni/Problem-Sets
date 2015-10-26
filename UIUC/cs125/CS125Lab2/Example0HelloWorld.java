public class Example0HelloWorld {

	/**
	 * An example Hello World program written for Zen Graphics. The main
	 * function is the code that is executed when you run a program. This
	 * program calls the function drawText from the class Zen which is stored in
	 * a separate file, Zen.java. The function drawText takes three parameters,
	 * or inputs that allow the user to control how it works. In this case the
	 * function takes in the string that should be displayed on the screen, as
	 * well as the x and y coordinates of where the string should be displayed.
	 */
	public static void main(String[] args) {
		Zen.drawText("Hello World!", 100, 200);
	}
}