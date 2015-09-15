package edu.illinois.cs241.javavsc;


public class CGlue {
    static {
        System.loadLibrary("ndkModule");
    }

   // Hint Use javah to generate C function declarations for these functions
    // e.g. javah edu.illinois.cs241.javavsc.CGlue
    // Then you can use these as a starting point for your program
    public static native String hello();
    public static native float findMin(float[] data);

}
