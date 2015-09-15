/**
 * Created by angrave on 4/14/15.
 * This Camera Preview has been tested on a Nexus5 (5.1 API22) and a Dragon Y88X Tablet (4.4.2 API 19)
 * YMMV on other devices
 */
package edu.illinios.cs241.webcam;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.ImageFormat;

import android.graphics.Rect;
import android.graphics.SurfaceTexture;
import android.graphics.YuvImage;
import android.hardware.Camera;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.io.ByteArrayOutputStream;
import java.util.List;


// See http://stackoverflow.com/questions/6478375/how-can-i-manipulate-the-camera-preview/6564924#6564924
@SuppressWarnings("deprecation")
@TargetApi(19)
public class MyCameraPreview extends SurfaceView implements SurfaceHolder.Callback, Camera.PreviewCallback {
    private static final String TAG = "MyCameraPreview";

    private SurfaceHolder mHolder;
    private SurfaceTexture mCameraTexture; // needs to be field to avoid GarbageCollector

    private Camera mCamera;
    private int mCameraWidth, mCameraHeight;
    private int mImageFormat = ImageFormat.NV21;

    private boolean mPreviewRunning;

    private int[] mCameraDecodedRGB;

    // Keep a jpg copy for the webserver
    private byte[] mJpegBytes;
    private boolean mNewBytesNeeded;

    public MyCameraPreview(Context context, AttributeSet attrs) {
        super(context, attrs);
        mHolder = getHolder();
        mHolder.addCallback(this);
        mHolder.setKeepScreenOn(true);
    }

    public synchronized void surfaceChanged(SurfaceHolder holder, int format, int width,
                               int height) {
    }

    public synchronized void surfaceCreated(SurfaceHolder holder) {
        Log.d(TAG, "surfaceCreated....");
        if (mPreviewRunning)
            return;

        //this.setWillNotDraw(false);

        openFrontFacingCamera();
    }


    private void openFrontFacingCamera() {

        mCamera = null;
        Camera.CameraInfo info = new Camera.CameraInfo();
        int numCameras = Camera.getNumberOfCameras();
        for (int i = 0; mCamera == null && i < numCameras; i++) {
            try {
                Camera.getCameraInfo(i, info);

                if (info.facing != Camera.CameraInfo.CAMERA_FACING_FRONT)
                    continue;

                mCamera = Camera.open(i);

            } catch (RuntimeException e) {
                Log.e(TAG, "Camera.open() failed", e);
            }
        }

        // Give up. Just try to open the default camera

        if (mCamera == null)
            mCamera = Camera.open();

        initializeCamera();
    }

    private void initializeCamera() {

        Camera.Parameters p = mCamera.getParameters();
        // Hack for Samsung devices (e.g. Nexus 5) ; otherwise callback is never called
        // See http://stackoverflow.com/questions/5788993/use-android-camera-without-surface-view
        try {
            mCameraTexture = new SurfaceTexture(10);
            mCamera.setPreviewTexture(mCameraTexture);
        } catch (Throwable ignored) {

        }

        // Choose smallest preview size available
        List<Camera.Size> sizes = p.getSupportedPictureSizes();
        int bestIndex = -1;
        int pixelCount = Integer.MAX_VALUE;

        for (int i = 0; i < sizes.size(); i++) {
            int w = sizes.get(i).width, h = sizes.get(i).height;
            int count = w * h;
            if (count < pixelCount) {
                bestIndex = i;
                pixelCount = count; // Note pixelCount is reused below
            }
        }

        Camera.Size size = sizes.get(bestIndex);

        mCameraWidth = size.width;
        mCameraHeight = size.height;

        Log.d(TAG, "W:" + mCameraWidth + ",H:" + mCameraHeight + ", num pixels:" + pixelCount);
        mCameraDecodedRGB = new int[pixelCount];

        p.setPreviewSize(mCameraWidth, mCameraHeight);
        p.setPreviewFormat(ImageFormat.NV21);
        mCamera.setParameters(p);

        int bitsPerPixel = ImageFormat.getBitsPerPixel(p.getPreviewFormat());
        int bytes = (pixelCount * bitsPerPixel) / 8;
        // Double Buffer - allow a buffer to be filled with new data while we are using the other one
        mCamera.addCallbackBuffer(new byte[bytes]);
        mCamera.addCallbackBuffer(new byte[bytes]);

        mCamera.setPreviewCallbackWithBuffer(this);
        mPreviewRunning = true;

        mCamera.startPreview();
        Log.d(TAG,"startPreview()");
    }

    public synchronized void surfaceDestroyed(SurfaceHolder holder) {

        try {
            if (mCamera != null) {
                mCamera.stopPreview();
                mPreviewRunning = false;
                // Race condition in Android Camera API
                // Allow inflight preview messages to be processed
                // before we release the camera
                final Camera c = mCamera;
                post(new Runnable() {
                    public void run() {
                        c.release();

                    }
                });

            }
        } catch (Exception e) {
            Log.e("Camera", e.getMessage());
        }
    }

    public synchronized void onPreviewFrame(byte[] data, Camera camera) {
        // Log.d(TAG,"onPreviewFrame ");
        Canvas canvas = null;
        try {

            canvas = mHolder.lockCanvas(null);

            if(canvas == null || ! mPreviewRunning) {
                Log.d(TAG,"canvas is null or preview is not active");
                return; /* View isnt ready for the data */
            }

            int canvasWidth = canvas.getWidth();
            int canvasHeight = canvas.getHeight();

            publish(data);

            DecodePixelUtil.decodeYUV(mCameraDecodedRGB, data, mCameraWidth, mCameraHeight);

            //updateBroadcast(data);


            canvas.save();
            canvas.scale(canvasWidth / (float) mCameraWidth, canvasHeight / (float) mCameraHeight);
            canvas.drawBitmap(mCameraDecodedRGB, 0/*offset*/, mCameraWidth /*array stride*/, 0, 0, mCameraWidth, mCameraHeight, false, null);
            canvas.restore();


        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            camera.addCallbackBuffer(data); // buffer can be re-used

            if (canvas != null) {
                mHolder.unlockCanvasAndPost(canvas);
            }
        }
    }

    void publish(byte[] data) {
        if(mNewBytesNeeded) {
            try {
                YuvImage yuvimage = new YuvImage(data, mImageFormat, mCameraWidth, mCameraHeight, null);
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                int quality = 50;
                Rect rect = new Rect(0, 0, mCameraWidth, mCameraHeight);
                boolean ok = yuvimage.compressToJpeg(rect, quality, baos);
                if (ok) { mJpegBytes = baos.toByteArray(); mNewBytesNeeded = false;}
            }catch(Exception ex) {
                Log.e(TAG,"YuvImage:"+ex.getMessage(),ex);
            }
        }
    }
    // Callback from activity (which in turn is called by jni code)
    public byte[] getRecentImageBytes() {
        mNewBytesNeeded = true;
        return mJpegBytes;
    }
}
