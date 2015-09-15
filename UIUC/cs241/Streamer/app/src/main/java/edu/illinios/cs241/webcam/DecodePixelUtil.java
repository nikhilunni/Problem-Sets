package edu.illinios.cs241.webcam;

/**
 * Created by angrave on 4/14/15.
 * Minor performance improvements compared to original stackoverflow version
 * Todo: Is YUVImage more performant? If not, consider converting this to a native function?
 * Todo: On modern CPUs is a single multiplication faster than multiple shift and adds?
 *
 * Attribution: http://stackoverflow.com/questions/6478375/how-can-i-manipulate-the-camera-preview
 */
public class DecodePixelUtil {
    /**
     * Decodes YUV frame to a buffer which can be use to create a bitmap. use
     * this for OS < FROYO which has a native YUV decoder decode Y, U, and V
     * values on the YUV 420 buffer described as YCbCr_422_SP by Android
     *
     * @param out
     *            the outgoing array of RGB bytes
     * @param fg
     *            the incoming frame bytes
     * @param width
     *            of source frame
     * @param height
     *            of source frame

     */
    public static void decodeYUV(final int[] out, final byte[] fg, final int width, final int height)  {
        final int sz = width * height;
        int i, j;
        int Y, Cr = 0, Cb = 0;
        int pixPtr = 0;
        for (j = 0; j < height; j++) {

            int cOff = sz + (j >> 1) * width;
            for (i = 0; i < width; i++) {
                Y = fg[pixPtr];

                if ((i & 0x1) == 0) {

                    Cb = fg[cOff++];
                    Cr = fg[cOff++];
                    if (Cb < 0)
                        Cb += 127;
                    else
                        Cb -= 128;
                    if (Cr < 0)
                        Cr += 127;
                    else
                        Cr -= 128;
                }
                if (Y < 0)
                    Y += 255;
                int R = Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5) + Y;
                int G = Y - (Cb >> 2) + (Cb >> 4) + (Cb >> 5) - (Cr >> 1) + (Cr >> 3) + (Cr >> 4) + (Cr >> 5);
                int B = Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6);
                // Todo: Reduce branching for 99.99% typical case that R,G,B are all in range

                // if (Rok && Gok && Bok) write else slow logic
                if (R < 0)
                    R = 0;
                else if (R > 255)
                    R = 255;
                if (G < 0)
                    G = 0;
                else if (G > 255)
                    G = 255;
                if (B < 0)
                    B = 0;
                else if (B > 255)
                    B = 255;
                out[pixPtr++] = 0xff000000 | (B << 16) | (G << 8) | R;
            }
        }

    }
}
