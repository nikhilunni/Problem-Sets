//UIUC CS125 FALL 2013 MP. File: Queue.java, CS125 Project: Challenge5-DataStructures, Version: 2013-10-14T15:32:35-0500.796362776
/**
 *@author nunni2
 */
public class Queue {
	
	private double[] queue = new double[0];
	

	/** Adds the value to the front of the queue.
	 * Note the queue automatically resizes as more items are added. */
	public void add(double value) {
		double[] queue2 = new double[queue.length+1];
		for(int i = 0; i < queue.length; i++) 
			queue2[i] = queue[i];
		queue2[queue2.length-1] = value;
		queue = queue2;
	}
	/** Removes the value from the end of the queue. If the queue is empty, returns 0 */
	public double remove() {
		if(queue.length <= 0)
			return 0;
		double[] queue2 = new double[queue.length-1];
		for(int i = 1; i < queue.length; i++)
			queue2[i-1] = queue[i];
		double output = queue[0];
		queue = queue2;
		return output;
	}
	
	/** Returns the number of items in the queue. */
	public int length() {
		return queue.length;	
	}
	
	/** Returns true iff the queue is empty */
	public boolean isEmpty() {
		return queue.length==0;
	}
	
	/** Returns a comma separated string representation of the queue. */
	public String toString() {
		String output = "";
		for(int i = 0; i < queue.length; i++) {
			output += queue[i];
			if(i < queue.length-1)
				output += ",";
		}
		return output;
	}
}
