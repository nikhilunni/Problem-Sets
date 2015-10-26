//UIUC CS125 FALL 2013 MP. File: GridCounting.java, CS125 Project: Challenge7-RecursiveKnight, Version: 2013-11-12T10:38:50-0600.575917765
/*
 * @author nunni2
 */
public class GridCounting {
	/** Returns the total number of possible routes (paths) from
	 * (x,y) to (tx,ty).
	 * There are only three valid kinds of moves:
	 *  Increment x by one.
	 *  Increment x by two.
	 *  Increment y by one.
	 *  
	 *  Hint: You'll need to test two base cases.
	 */
	public static int count(int x,int y, int tx, int ty) {

		if(x > tx || y > ty) {
			return 0;
		}
			
		if(x == tx && y == ty)
			return 1;
		
		return count(x+1,y,tx,ty) + count(x+2,y,tx,ty) + count(x,y+1,tx,ty);
	}
	
	public static void main(String[] args) {
		System.out.println(count(7,15,10,15));
	}
}
