public class Example2SpriteMoveFlipBuffer {

	/**
	 * Drawing a sprite using a two buffers. When the scene is ready to be
	 * displayed, call 'flipBuffer' to present the new image to the user.
	 * 
	 **/
	public static void main(String[] args) {
        // This is a more advanced example.
		//
		// A buffer is place where you can assemble an entire image before
		// showing it on screen
		//
		// With flipBuffer: Changes are written to a secret background buffer
		// first
		// When flipBuffer is called, the background buffer and the foreground
		// buffer are swapped, revealing the new image.

		// When flipBuffer is called one (or more times)
		// Zen stops painting immediately to the screen and instead uses a
		// behind-the-scenes buffer
		// to assemble the next complete image to display.
		int x = 100;
		while (true) { // this loop will run repeatedly until the program is
						// exited
			Zen.drawImage("sprite1.gif", x, 200);

			Zen.flipBuffer();
			Zen.sleep(50); // 50 milliseconds (1/20th second)
			x = x + 5; // changes the x-coordinate of where the image will be
						// drawn next
		} // while
	} // main
}
