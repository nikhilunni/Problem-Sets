//UIUC CS125 FALL 2013 MP. File: PlayListUtil.java, CS125 Project: Challenge4-Photoscoop, Version: 2013-10-05T05:38:13-0500.017648101
/**
 * Add you netid here..
 * @author angrave
 *
 */
public class PlayListUtil {

	/**
	 * Debug ME! Use the unit tests to reverse engineer how this method should work.
	 * Hint: Fix the formatting (shift-cmd-F) to help debug the following code
	 * @param list
	 * @param maximum
	 */
	
	public static void main(String[] args) {
		String[] testData = new String[] { "CC", "DD", "EE" };
		for(String i : add(testData,"XX", true)) 
			System.out.println(i);
	}
	public static void list(String[] list, int maximum) {
		for (int i = 0; i < maximum || (maximum<0 && i < list.length); i++)
		{
			TextIO.putln((i+1) + ". " + list[i]);
		}
	}

	/**
	 * Appends or prepends the title
	 * @param list
	 * @param title
	 * @param prepend if true, prepend the title otherwise append the title
	 * @return a new list with the title prepended or appended to the original list
	 */
	public static String[] add(String[] list, String title, boolean prepend) {
		String[] output = new String[list.length+1];
		if(prepend) {
			output[0] = title;
			for(int i = 0; i < list.length; i++) 
				output[i+1] = list[i];
		}
		else {
			for(int i = 0; i < list.length; i++) 
				output[i] = list[i];
			output[output.length-1] = title;
		}
		return output;
	}
	/**
	 * Returns a new list with the element at index removed.
	 * @param list the original list
	 * @param index the array index to remove.
	 * @return a new list with the String at position 'index', absent.
	 */
	public static String[] discard(String[] list, int index) {
		String[] output = new String[list.length-1];
		for(int i = 0; i < index; i++) 
			output[i] = list[i];
		for(int i = index+1; i < list.length; i++)
			output[i-1] = list[i]; 
		return output;
	}

}
