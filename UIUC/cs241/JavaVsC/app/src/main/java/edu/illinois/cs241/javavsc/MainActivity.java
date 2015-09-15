package edu.illinois.cs241.javavsc;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends ActionBarActivity {

    public static final int DATA_SIZE=30000; /* Array size */


    Thread mBenchmarkThread; /* Currently executing thread */
    TextView mTextView; /* Output view */
    Button mStartButton; /* The start button */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextView = (TextView) findViewById(R.id.results);

        mStartButton = (Button)findViewById(R.id.gobtn);

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

        mTextView.setText(CGlue.hello() + "\nData size: " + DATA_SIZE + " floats\nPress the button to, well, start...");
    }

    public static float[] createFloatData(int N) {
        float[] result = new float[N];
        for(int i =0; i < N;i++) result[i] = (float) Math.random();
        return result;
    }
    public static float findMinimum(float[] data) {
        float result = data[0];
        for(int i = 1; i < data.length;i++)
            if(data[i] < result) result = data[i];
        return result;

    }
    public int benchmarkJava(float[] data) {
        long startTime = System.currentTimeMillis();
        long endTime = startTime + 1000;
        int iterCount = 0;
        for(; System.currentTimeMillis() < endTime; iterCount++ )
            findMinimum(data);
        return iterCount;
    }

    public int benchmarkC(float[] data) {
        long startTime = System.currentTimeMillis();
        long endTime = startTime + 1000;
        int iterCount = 0;
        for(; System.currentTimeMillis() < endTime; iterCount++ )
            CGlue.findMin(data);
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
        float jresult = findMinimum(data);
        float cresult = CGlue.findMin(data);

        mTextView.append("Java result="+jresult+", c result="+cresult+"\n");
        if(jresult != cresult) {
            mTextView.append("Not the same!\n");
        }
        /* The UI thread cannot be stalled for more than a second or two.
        For benchmarking purposes we need another thread to perform the calculation in the background
         */
        mBenchmarkThread = new Thread() {
            public void run() {
                int runs  = 5; /* Run each benchmark 5 times */

                int[][] results = new int[runs][2];
                for(int i=0;i<runs;i++) {

                    results[i][0] = benchmarkJava(data);
                    results[i][1] = benchmarkC(data);

                    /* Post the results to the screen using the UI thread */
                    reportResult("Java: " + results[i][0] + ", C:" + results[i][1] + " iterations per second");
                }

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
