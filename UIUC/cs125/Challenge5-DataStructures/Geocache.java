//UIUC CS125 FALL 2013 MP. File: Geocache.java, CS125 Project: Challenge5-DataStructures, Version: 2013-10-14T15:32:35-0500.796362776
/**
 * Create a class 'Geocache' with two private instance variables 'x' 'y' of type double and a private integer 'id'
 * .
 * A class variable 'count' will also be required to count the number of times a Geocache object has been created (instantiated).
 * Create two constructors - one which takes two double parameters (the initial values of x,y). The
 * second constructor will take another Geocache and initialize itself based on that geocache.
 * 
 * For both constructors set the Geocache's id to the current value of count (thus the first geocache will have the value zero)
 * when the Geocache is created, then increment the count value. 
 * 
 * Also create 'resetCount()' and getNumGeocachesCreated() which returns an int - the number of geocaches created since 
 * resetCount() method was called.
 * 
 * Create an equals method that takes an object reference and returns true if the given object equals this object.
 * Hint: You'll need 'instanceof' and cast to a (Geocache)
 * 
 * Create a toString() method that returns a string representation of this object in the form '(x,y)' where 'x' and 'y'
 * are the current values of x,y.
 * 
 * Create the four getX/getY/setX/setY methods for x,y.
 * However the setX() method will only change the Geocache's x value if the given value is between -1000 and 1000 exclusive (i.e. -1000<x<1000).
 * If the value is outside of this range, the new value is ignored and the Geocache's x value remains unchanged.
 *   
 * Create a get method for id.
 * 
 * @author nunni2
 */
class Geocache {
	private double x;
	private double y;
	private int id;
	private static int numGeocaches = 0;
	
	public Geocache(double x, double y) {
		this.x = x;
		this.y = y;
		id = numGeocaches;
		numGeocaches++;
		
	}
	public Geocache(Geocache geo) {
		x = geo.getX();
		y = geo.getY();
		id = numGeocaches;
		numGeocaches++;
	}
	
	public static void resetCount() {
		numGeocaches = 0;
	}
	
	public static int getNumGeocachesCreated() {
		return numGeocaches;
	}
	public void setX(double x) {
		this.x = (x>-1000 && x<1000) ? x : this.x;
	}
	public double getX() {
		return x;
	}
	public void setY(double y) {
		this.y = y;
	}
	public double getY() {
		return y;
	}
	public int getId() {
		return id;
	}
	public boolean equals(Object other) {
		if(other instanceof Geocache) {
			Geocache temp = (Geocache)other;
			return temp.getX() == x && temp.getY() == y;
		}
		return false;
	}
	public String toString() {
		return "(" + x + "," + y + ")";
	}
	
}
