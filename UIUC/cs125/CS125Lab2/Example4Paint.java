public class Example4Paint {

	/**
	 * A simple paint program. Press any modifier key (e.g shift) or mouse
	 * button to paint.
	 */
	public static void main(String[] args) {
		// creates a new window of with dimensions 320 by 200
		// Also allows you to put in several options that are defined
		// in the Zen class. "stretch" makes sure that the entire window
		// is filled in
		Zen.create(320, 200, "stretch");

		while (Zen.isRunning()) {
			int x = Zen.getMouseX();
			int y = Zen.getMouseY();

			// this code will run if any button or mouse key is held down
			if (Zen.getMouseButtonsAndModifierKeys() != 0) {
				// Math.random() chooses a random number x; 0<x<1
				double x2 = x - 25 + 50 * Math.random();
				double y2 = y - 25 + 50 * Math.random();
				// (int) converts the double x2 into an integer
				Zen.fillRect((int) x2, (int) y2, 1, 1);
			}
		}
	}
}
