public class Example1OnceUponAWhile {

	/**
	 * A simple program that displays some text.
	 */
	public static void main(String[] args) {

		Zen.setFont("Times-50");
		Zen.drawText("Once", 0, 100);

		Zen.sleep(500); // tells the thread to pause for x amount of
						// milliseconds

		Zen.setColor(255, 0, 0); // red, green, blue
		Zen.drawText("Upon", 0, 200);

		Zen.setColor(0, 0, 128); // red, green, blue
		Zen.drawText("A Time (please click)", 0, 300);

		Zen.waitForClick(); // tells the thread to stop until a mouse button is
							// clicked
		int shade = 255;
		while (shade > 0) { // the instructions within these braces will be
							// repeated until shade = 0
			Zen.setColor(shade, shade, shade);
			Zen.fillRect(0, 0, 640, 480); // x-coord, y-coord, width, height
			Zen.sleep(1);
			shade = shade - 1; // this is where the shade variable is changed
								// each time the loop executes once
		}
		Zen.setColor(200, 200, 0);
		Zen.drawText("The end", 0, 200);
	} // main
} // class
