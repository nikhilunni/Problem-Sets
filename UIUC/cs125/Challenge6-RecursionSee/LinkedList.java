//UIUC CS125 FALL 2013 MP. File: LinkedList.java, CS125 Project: Challenge6-RecursionSee, Version: 2013-11-05T17:19:55-0600.019560079
/**
 * @author nunni2
 *
 */
public class LinkedList {
	// Get and Set methods are NOT necessary!

	private LinkedList next; 	
	private final String word;

	/** Constructs this link.
	 * @param word ; a single word (never null).
	 * @param next ; the next item in the chain (null, if there are no more items).
	 */
	public LinkedList(String word, LinkedList next) {
		this.word = word;
		this.next = next;
	}

	/**
	 * Converts the entire linked list into a string representation.
	 */
	public String toString() {
		if (next == null)
			return word;// BASE CASE; no more recursion required

		// Recursive case:
		String restOfString = next.toString(); // Forward Recursion
		return word + ";" + restOfString;
	}

	/**
	 * Returns the number of entries in the linked list.
	 * @return number of entries.
	 */
	public int getCount() {
		if (next == null)
			return 1; // BASE CASE; no more recursion required!

		// Recursive case:
		return 1 + next.getCount(); // Forward recursion
	}
	
	/** Creates a new LinkedList entry at the end of this linked list.
	 * Recursively finds the last entry then adds a new link to the end.
	 * @param word
	 */
	public void append(String word) {
		if (next == null)
			next = new LinkedList(word, null);
		else
			next.append(word);

	}
	/**
	 * Recursively counts the total number of letters used.
	 * 
	 * @return total number of letters in the words of the linked list
	 */
	public int getLetterCount() {
		if(next == null)
			return word.length();
		return word.length() + next.getLetterCount();
	}

	/**
	 * Recursively searches for and the returns the longest word.
	 * @return the longest word i.e. word.length() is maximal.
	 */
	public String getLongestWord() {
		if(next == null)
			return word;
		String nextGreatest = next.getLongestWord();
		return (word.length() > nextGreatest.length() ? word : nextGreatest);
	}

	/** Converts linked list into a sentence (a single string representation).
	* Each word pair is separated by a space.
	* A period (".") is appended after the last word.
	* The last link represents the last word in the sentence.*/
	public String getSentence() {
		if(next == null)
			return word + ".";
		return word + " " + next.getSentence();
	}
	
	/**
	 * Converts linked list into a sentence (a single string representation).
	 * Each word pair is separated by a space. A period (".") is appended after
	 * the last word. The last link represents the first word in the sentence
	 * (and vice versa). The partialResult is the partial string constructed
	 * from earlier links. This partialResult is initially an empty string. 
	 */
	public String getReversedSentence(String partialResult) {
		if(next == null) 
			return word + (partialResult.length()==0 ? "." : "");
		return next.getReversedSentence(partialResult+" " + word) + " " + word + (partialResult.length()==0 ? "." : "");
	}

	/** Creates a linked list of words from an array of strings.
	 * Each string in the array is a word. */
	public static LinkedList createLinkedList(String[] words) {
		
		if(words.length == 1)
			return new LinkedList(words[0], null);
		
		String[] remainingWords = new String[words.length-1];
		for(int i = 0; i < remainingWords.length; i++)
			remainingWords[i] = words[i+1];
		return new LinkedList(words[0], createLinkedList(remainingWords));
	}

	/**
	 * Searches for the following word in the linked list. Hint: use .equals not ==
	 * to compare strings.
	 * 
	 * @param word
	 * @return true if the linked list contains the word (case sensivitive)
	 */
	public boolean contains(String word) {
		if(this.word.equals(word))
			return true;
		if(next == null)
			return false;
		return next.contains(word);
	}
	


	/** Recursively searches for the given word in the linked list.
	 * If this link matches the given word then return this link.
	 * Otherwise search the next link.
	 * If no matching links are found return null.
	 * @param word the word to search for.
	 * @return The link that contains the search word.
	 */
	public LinkedList find(String word) {
		if(this.word.equals(word))
			return this;
		if(next == null)
			return null;
		return next.find(word);

	}

	/**
	 * Returns the last most link that has the given word, or returns null if
	 * the word cannot be found.
	 * Hint: Would forward recursion be useful?
	 * @param word the word to search for.
	 * @return the last LinkedList object that represents the given word, or null if it is not found.
	 */
	public LinkedList findLast(String word) {
		if(next == null) {
			if(this.word.equals(word))
				return this;
			else
				return null;
		}		
		if(this.word.equals(word) && next.findLast(word) == null)
			return this;
		
		return next.findLast(word);
	}

	public LinkedList insert(String string) {
		if(next == null)
			next = new LinkedList(string, null);
		else if(string.compareTo(word) > 0 && string.compareTo(next.word) > 0)
			next.insert(string);
		else if(string.compareTo(word) > 0 && string.compareTo(next.word) <= 0)
			next = new LinkedList(string, next);
		else
			return new LinkedList(string, this);
		return this;
	}
}
