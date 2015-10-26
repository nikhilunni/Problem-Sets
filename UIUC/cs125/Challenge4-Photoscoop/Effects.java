//UIUC CS125 FALL 2013 MP. File: Effects.java, CS125 Project: Challenge4-Photoscoop, Version: 2013-10-05T05:38:13-0500.017648101
/*A class to delegate each effect request.
 * The process method is called whenever the user selects a menu item.
 * However it wouldnt be hard to build a batch program that also uses this process method.
 * 
 * Todo: Put your netid (i.e. username) in the line below
 * 
 * @author nunni2
 */
public class Effects {
	/**
	 * Returns a new image (2D array) based on the command and the source parameters.
	 * This method delegates all of the work to PixelEffects class
	 * @param cmd - the command to execute
	 * @param source - the primary image source (not changed)
	 * @param background - the secondary (background) image (not changed)
	 * @return the new image or null if the command failed.
	 */
	public static int[][] process(String cmd, int[][] source, int[][] background) {
		
		if(cmd.equals("half"))
			return PixelEffects.resize(source, source.length/2, source[0].length/2);
		if(cmd.equals("rotate")) 
			return PixelEffects.rotateLeft(source);
		if(cmd.equals("flip")) 
			return PixelEffects.flip(source);
		if(cmd.equals("mirror"))
			return PixelEffects.mirror(source);
		if(cmd.equals("redeye"))
			return PixelEffects.redeye(source, background);
		if(cmd.equals("funky"))
			return PixelEffects.funky(source, background);
		if(cmd.equals("resize"))
			return PixelEffects.resize(source, background);
		if(cmd.equals("merge"))
			return PixelEffects.merge(source, background);
		if(cmd.equals("key"))
			return PixelEffects.chromaKey(source, background);
		
		
		System.out.println("Todo: Implement Effects.process("+cmd+")");
		throw new RuntimeException("Unknown command:"+cmd);
	}// end method

} // end class
