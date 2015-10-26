//UIUC CS125 FALL 2013 MP. File: PixelEffects.java, CS125 Project: Challenge4-Photoscoop, Version: 2013-10-05T05:38:13-0500.017648101

/* A class to implement the various pixel effects.
 *
 * Todo: Put your netid (i.e. username) in the line below
 * 
 * @author nunni2
 */
public class PixelEffects {

	static int[][] exampleMatrix = new int[][]{ { 0, 1, 2, 3 }, 
												{ 10, 11, 12, 13 },
												{ 20, 21, 22, 23 } };
	
	public static boolean equals(int[][] array1, int[][] array2) {
		for(int i = 0; i < array1.length; i++) {
			for(int j = 0; j < array1[i].length; j++) {
				if(array1[i][j] != array2[i][j])
					return false;
			}
		}
		return true;
	}
	public static void main(String[] args) {
		int[][] source = { { 0, 0x44, 0x5500, 0x660000 } } ;
		int[][] newInt = { { 0, 0x44, 0x5500, 0x660000 } } ;
		for(int i = 0; i < source[0].length; i++)
			System.out.println(source[0][i]);
		
		
	}
	/** Copies the source image to a new 2D integer image */
	public static int[][] copy(int[][] source) {
		int[][] newPic = new int[source.length][source[0].length]; //Assuming no holes
		for(int x = 0; x < source.length; x++) {
			for(int y = 0; y < source[0].length; y++) {
				newPic[x][y] = source[x][y];
			}
		}
		return newPic;
	}
	
	public static void dump(int[][] matrix) {
		for(int i = 0; i < matrix.length;i++) {
			for(int j = 0; j < matrix[0].length;j++) {
				System.out.print(matrix[i][j] + "\t");
			}
			System.out.println();
		}
		
	}
	/**
 	 * Resize the array image to the new width and height
	 * You are going to need to figure out how to map between a pixel
	 * in the destination image to a pixel in the source image
	 * @param source
	 * @param newWidth
	 * @param newHeight
	 * @return
	 */
	public static int[][] resize(int[][] source, int newWidth, int newHeight) {
		int[][] newPic = new int[newWidth][newHeight];
		double scaleX = (double)source.length / newWidth;
		double scaleY = (double)source[0].length / newHeight;
		for(int i = 0; i < newWidth; i++) {
				for(int j = 0; j < newHeight; j++) {
						newPic[i][j] = source[(int)(i*scaleX)][(int)(j*scaleY)];
				}
		}
		return newPic; // Fix Me
		// Hints: Use two nested for loops between 0... newWidth-1 and 0.. newHeight-1 inclusive.
		// Hint: You can just use relative proportion to calculate the x (or y coordinate)  in the original image.
		// For example if you're setting a pixel halfway across the image, you should be reading half way across the original image too.
	}

	/**
	 * Half the size of the image. This method should be just one line! Just
	 * delegate the work to resize()!
	 */
	public static int[][] half(int[][] source) {
		return resize(source,source.length/2, source[0].length/2);
	}
	
	/**
	 * Create a new image array that is the same dimesions of the reference
	 * array. The array may be larger or smaller than the source. Hint -
	 * this methods should be just one line - delegate the work to resize()!
	 * 
	 * @param source
	 *            the source image
	 * @param reference
	 * @return the resized image
	 */
	public static int[][] resize(int[][] source, int[][] reference) {
		return resize(source, reference.length, reference[0].length);
	}

	/** Flip the image vertically */
	public static int[][] flip(int[][] source) {
		int[][] flipped = new int[source.length][source[0].length];
		for(int i = 0; i < source.length; i++) {
			for(int j = 0; j < source[0].length; j++) {
				flipped[i][j] = source[i][source[0].length-j-1];
			}
		}
		
		return flipped;
	}

	/** Reverse the image horizontally */
	public static int[][] mirror(int[][] source) {
		int[][] mirrored = new int[source.length][source[0].length];
		for(int i = 0; i < source.length; i++) {
			for(int j = 0; j < source[0].length; j++) {
				mirrored[i][j] = source[source.length-i-1][j];
			}
		}
		
		return mirrored;
	}

	/** Rotate the image */
	public static int[][] rotateLeft(int[][] source) {
		int[][] rotated = new int[source[0].length][source.length];
		for(int i = 0; i < rotated.length; i++) {
			for(int j = 0; j < rotated[0].length; j++) {
				rotated[i][j] = source[rotated[0].length-j-1][i];
			}
		}
		
		return rotated;
	}

	/** Merge the red,blue,green components from two images */
	public static int[][] merge(int[][] sourceA, int[][] sourceB) {
		// The output should be the same size as the input. Scale (x,y) values
		// when reading the background
		// (e.g. so the far right pixel of the source is merged with the
		// far-right pixel ofthe background).
		int blueMask = 0xFF;
		int greenMask = 0xFF << 8;
		int redMask = 0xFF << 16;
		int[][] scaledB = resize(sourceB, sourceA);
		int[][] output = new int[sourceA.length][sourceA[0].length];
		for(int i = 0; i < scaledB.length; i++) {
			for(int j = 0; j < scaledB[0].length; j++) {
				output[i][j] += ((scaledB[i][j] & blueMask) + (sourceA[i][j] & blueMask)) / 2;
				output[i][j] += (((scaledB[i][j] & greenMask) + (sourceA[i][j] & greenMask)) / 2) & greenMask;
				output[i][j] += (((scaledB[i][j] & redMask) + (sourceA[i][j] & redMask)) / 2) & redMask;
			}
		}
		return output;
	}

	/**
	 * Replace the green areas of the foreground image with parts of the back
	 * image
	 */
	public static int[][] chromaKey(int[][] foreImage, int[][] backImage) {
		int[][] newBack = resize(backImage, foreImage);
		int[][] output = new int[foreImage.length][foreImage[0].length];
		for(int i = 0; i < foreImage.length; i++) {			
			for(int j = 0; j < foreImage[0].length; j++) { 
				int green = RGBUtilities.toGreen(foreImage[i][j]);
				int blue = RGBUtilities.toBlue(foreImage[i][j]);
				int red = RGBUtilities.toRed(foreImage[i][j]);
				if(green > 80)
					output[i][j] = newBack[i][j];
				else
					output[i][j] = foreImage[i][j];
			}
		}
		
		return output;
	}

	/** Removes "redeye" caused by a camera flash. sourceB is not used */
	public static int[][] redeye(int[][] source, int[][] sourceB) {

		int width = source.length, height = source[0].length;
		int[][] result = new int[width][height];
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++) {
				int rgb = source[i][j];
				int red = RGBUtilities.toRed(rgb);
				int green = RGBUtilities.toGreen(rgb);
				int blue = RGBUtilities.toBlue(rgb);
				if (red > 4 * Math.max(green, blue) && red > 64)
					red = green = blue = 0;
				result[i][j] = RGBUtilities.toRGB(red, green, blue);
			}

		return result;
	}

	/* Upto you! do something fun to the image */
	public static int[][] funky(int[][] source, int[][] sourceB) {
		int[][] funkedUp = new int[source.length][source[0].length];

		for(int i = 0; i < source.length; i++) {			
			for(int j = 0; j < source[0].length; j++) { 
				int green = 255 - RGBUtilities.toGreen(source[i][j]);
				int blue = 255 - RGBUtilities.toBlue(source[i][j]);
				int red = 255 - RGBUtilities.toRed(source[i][j]);
				
				funkedUp[i][j] = RGBUtilities.toRGB(red, green, blue);
			}
		}
		
		return funkedUp;
	}
}
