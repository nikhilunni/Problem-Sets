/* Original version by Lawrence Angrave 2015 for CS 241 @ Illinois edu */
package edu.illinios.cs241.javavsandroidthreads;

import android.os.Bundle;
import android.os.SystemClock;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import edu.illinios.cs241.javavsandroidthreads.MultithreadedNativeBenchmark;
import edu.illinios.cs241.javavsandroidthreads.R;


public class MainActivity extends ActionBarActivity {

    public static final int DATA_SIZE=320*240; /* Array size represents a small thumbnail picture */


    Thread mBenchmarkThread; /* Currently executing thread */
    TextView mTextView; /* Output view */
    Button mStartButton; /* The start button */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextView = (TextView) findViewById(R.id.results);

        mStartButton = (Button)findViewById(R.id.gobtn);


        try {
            System.loadLibrary("mynativelibrary");

            mTextView.setText(MultithreadedNativeBenchmark.hello() + "\nData size: " + DATA_SIZE + " floats\nPress the button to, well, start...");
            // Hide the start button while the benchmark is running
            mStartButton.setOnClickListener(
                    new View.OnClickListener() {
                        @Override
                        public void onClick(View v) {
                            v.setVisibility(View.GONE);
                            runBenchmark();
                        }
                    }
            );
        } catch(Throwable ex) {
            mTextView.setText(ex.getMessage());
            mStartButton.setVisibility(View.GONE);
        }
    }

    public static float[] createFloatData(int N) {
        float[] result = new float[N];
        for(int i =0; i < N;i++) result[i] = (float) Math.random();
        return result;
    }

    public static float calculate(float[] data) {
        float result = Float.MAX_VALUE;
        for(int i = 0; i < data.length;i++) {
            float val = (float) Math.cos(data[i]);
            // Assume val is used e.g. written into an array somwehere
            //  - Otherwise we can optimize as we know the range and could calculate cosine after the loop
            if(val < result) result = val;
        }
        return result;

    }
    public int benchmarkJava(float[] data) {
        final long startTime = System. nanoTime();
        final long duration = 1000000000;
        int iterCount = 0;
        for(; System.nanoTime()- startTime < duration; iterCount++ )
            calculate(data);
        return iterCount;
    }

    public int benchmarkC(float[] data) {
        final long startTime = System. nanoTime();
        final long duration = 1000000000;
        int iterCount = 0;
        for(; System.nanoTime()- startTime < duration; iterCount++ )
            MultithreadedNativeBenchmark.calculate(data);
        return iterCount;
    }
    public void reportResult(final String mesg) {
        /* We cannot directly append text to the text view because we are not
        running in the UI thread. Instead, create a small runnable object and
        post it on the UI queue to be run later by the UI thread
         */
        mTextView.post(new Runnable() {
            public void run() {
                mTextView.append(mesg);
                mTextView.append("\n");
            }
        });
    }

    public void runBenchmark() {
        mTextView.setText("Starting ...\nData Size:"+DATA_SIZE+" floats\n");
        final float[] data = createFloatData(DATA_SIZE);

        /* Check that Java and C calculate the same result */
        float jresult = calculate(data);
        float cresult = MultithreadedNativeBenchmark.calculate(data);

        mTextView.append("Java result="+jresult+"\n    c result="+cresult+"\n");
        if(jresult != cresult) {
            mTextView.append("\nNot the same! Fix the code!\n");
            return;
        }
        /* The UI thread cannot be stalled for more than a second or two.
        For ben chmarking purposes we need another thread to perform the calculation in the background
         */
        mBenchmarkThread = new Thread() {
            public void run() {
                int runs  = 5; /* Run each benchmark 5 times */

                int javaTotal = 0, cTotal = 0;
                for(int i=0;i<runs;i++) {
                    SystemClock.sleep(200); // Allow time for UI thread / system to settle
                    int javaIterations  =benchmarkJava(data);
                    SystemClock.sleep(200);  // Allow time for UI thread / system to settle
                    int cIterations = benchmarkC(data);

                    /* Post the results to the screen using the UI thread */
                    reportResult("Java: " + javaIterations + ", C:" + cIterations + " iterations per second");

                    javaTotal += javaIterations;
                    cTotal +=cIterations;
                }
                if(javaTotal >0 && cTotal>0)
                    reportResult("\nAverage speed up: "+cTotal +" / " + javaTotal+" = "+String.format("%.1f", cTotal / (float) javaTotal));

                /* We've finished benchmarking. use the UI thread to redisplay the Start button */
                mTextView.post(new Runnable() {
                    public void run() {
                        mStartButton.setVisibility(View.VISIBLE);
                    }
                });
            }
        };
        mBenchmarkThread.start();
    }

    // Ignore the following boilerplate code
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    // Ignore the following boilerplate code
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
