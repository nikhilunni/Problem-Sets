import java.awt.Graphics2D;
import java.awt.Image;

public class Example7AdvancedGraphics2D {

	/**
	 * An advanced example: Rather than using the simple Zen calls We ask Zen to
	 * return a graphics2D object. This gives you the full power of Java's 2D
	 * Graphics drawing At the cost of some additional code complexity
	 */
	public static void main(String[] args) {
		Image image = Zen.getCachedImage("sprite1.gif");

		double theta = 0.1; // angles are in radians
		while (true) {
			// Always get the new BufferGraphics after calling flipBuffer
			// i.e. getBufferGraphics should be inside the loop
			Graphics2D g = Zen.getBufferGraphics();
			theta = theta + 0.01;
			if (theta > 2 * Math.PI)
				theta = theta - 2 * Math.PI;

			double x = Zen.getMouseX();
			double y = Zen.getMouseY();
			// Don't rotate the image
			// Instead rotate and scale the paper!
			// Translate the paper (now the origin is at the mouse position)
			// i.e. anything drawn now at (0,0) will appear at the mouse
			// position.
			g.translate(x, y);
			// Rotate the paper about it's (new) origin
			g.rotate(theta, 0, 0);
			// Scale (this will make the image larger)
			g.scale(2 + Math.cos(theta), 2 + Math.sin(theta));
			// Scale (make anything drawn to the paper even larger)
			g.scale(2, 2);
			// draw the image at the origin
			g.drawImage(image, 0, 0, null);
			// show the contents of the buffer
			Zen.flipBuffer();
			Zen.sleep(10);
		}
	}

}
