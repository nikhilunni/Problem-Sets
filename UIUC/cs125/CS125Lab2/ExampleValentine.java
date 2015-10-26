public class ExampleValentine {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String mesg = "Be my Valentine!";
		Zen.setColor(255, 0, 0);
		int i = 0;
		String part = "";
		Zen.setFont("Courier-20");
		double x = 640;
		while (x > 1) {
			Zen.drawImage("wikimedia_Heart_numlabels.png", (int) x, 0);
			x = x * 0.9;
			Zen.sleep(33); // 33 milliseconds is 1/30th second
		}
		while (x <1000) {
			
			Zen.drawImage("wikimedia_Heart_numlabels.png", -(int) x, 0);
			x = x / 0.90;
			Zen.sleep(33); // 33 milliseconds is 1/30th second
		}
		Zen.setColor(0, 0, 0);
		Zen.fillRect(0, 0, 640, 480);
		while (true) {
			Zen.setColor(255, 0, 0);
			Zen.drawText("You stole my heart!",100,200);
			Zen.setColor(200, 120, 120);
			i = 0;
			part = "";
			while (i < mesg.length()) {
				part = part + mesg.charAt(i);
				Zen.drawText(part, 0, 100);
				Zen.sleep(100); // 100 ms is 1/10th second
				i = i + 1;
			}

			Zen.setColor(0, 0, 0);
			Zen.fillRect(0, 0, 640, 480);
		}

	}
}
