//UIUC CS125 FALL 2013 MP. File: StaticMethodsAreEasy.java, CS125 Project: Challenge5-DataStructures, Version: 2013-10-14T15:32:35-0500.796362776
public class StaticMethodsAreEasy {

/**
 *@author nunni2
 */

	/**
	 * Returns an array of num geocaches. Each geocache is initialized to a random
	 * (x,y) location.
	 * if num is less than zero, just return an empty array of length 0.
	 * 
	 * @param num
	 *            number of geocaches to create
	 * @return array of newly minted Points
	 */
	public static Geocache[] createGeocaches(int num) {
		if(num >= 0) {
			Geocache[] output = new Geocache[num];
			for(int i = 0; i < num; i++) {
				output[i] = new Geocache((int)(Math.random()*Integer.MAX_VALUE),(int)(Math.random()*Integer.MAX_VALUE));
			}
			return output;
		}
		return new Geocache[0];
		
	}
	
	/**
	 * Modifies geocaches if the geocache's X value is less than the allowable minimum
	 * value.
	 * 
	 * @param p
	 *            array of geocaches
	 * @param minX
	 *            minimum X value.
	 * @return number of modified geocaches (i.e. x values were too small).
	 */
	public static void ensureMinimumXValue(Geocache[] pts, double value) {
		for(Geocache g : pts) {
			if(g.getX() < value) {
				g.setX(value);
			}
		}
	}

	/**
	 * Counts the number of geocaches that are equal to the given geocache
	 * Hint: Use geocache.equals() method 
	 * @param p -
	 *            geocache array
	 * @param test -
	 *            test geocache (compared using .equal)
	 * @return number of matching geocaches
	 */
	public static int countEqual(Geocache[] g1, Geocache g2) {
		int num = 0;
		for(int i = 0; i < g1.length; i++) {
			if(g2.equals(g1[i]))
				num++;
		}
		return num;
	}
}
