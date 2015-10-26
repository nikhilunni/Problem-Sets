//UIUC CS125 FALL 2013 MP. File: Example_MathTutor.java, CS125 Project: Challenge2-Hollywood, Version: 2013-09-17T09:52:07-0500.008393307
public class Example_MathTutor {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		mathTutor();
	}

	public static void mathTutor() {
		int guess;
		
		boolean correct = false;
		// each time the beginning of the loop
		// evaluate correct == false
		// so if correct is false then we will go into the loop body again.

		while (correct == false) {
			TextIO.putln("What is 16 squared?");

			guess = TextIO.getlnInt();
			// Change the value of correct:
			// if guess is 256 then (guess == 256) will evaluate to true.
			// We will store either 'true' or 'false' inside correct:
			correct = (guess == 256);

			if (!correct) {
				TextIO.putln("Incorrect");
				TextIO.putln("Guess again!");
			}
		}
		TextIO.putln("Fabulous!");
	}

}
