//UIUC CS125 FALL 2013 MP. File: Stack.java, CS125 Project: Challenge5-DataStructures, Version: 2013-10-14T15:32:35-0500.796362776
/**
 *@author nunni2
 */
public class Stack {
	
	private String[] stack = new String[0];
	
	
	public static void main(String[] args) {
		Stack stack = new Stack();
		for(int i = 0; i < 10; i++)
			stack.push(i+"");
		System.out.println(stack.toString());
	}
	/** Adds a value to the top of the stack.*/
	public void push(String value){
		String[] stack2 = new String[stack.length+1];
		for(int i = 0; i < stack.length; i++) 
			stack2[i] = stack[i];
		stack2[stack2.length-1] = value;
		stack = stack2;
	}
	
	/** Removes the topmost string. If the stack is empty, returns null. */
	public String pop() {
		if(stack.length <= 0)
			return null;
		String output = stack[stack.length-1];
		String[] stack2 = new String[stack.length-1];
		for(int i = 0; i < stack.length-1; i++)
			stack2[i] = stack[i];
		stack = stack2;
		return output;
	}
	
	/** Returns the topmost string but does not remove it. If the stack is empty, returns null. */
	public String peek() {
		if(stack.length <= 0)
			return null;
		return stack[stack.length-1];
	}
	
	/** Returns true iff the stack is empty */
	public boolean isEmpty() {
		return stack.length==0;
	}

	/** Returns the number of items in the stack. */
	public int length() {
		return stack.length;
	}
	
	/** Returns a string representation of the stack. Each string is separated by a newline. Returns an empty string if the stack is empty. */
	public String toString() {
		if(stack.length <= 0)
			return "";
		String output = "";
		for(int i = 0; i < stack.length; i++) {
			output += stack[i] + "\n";
		}
			
		return output;
	}
}
