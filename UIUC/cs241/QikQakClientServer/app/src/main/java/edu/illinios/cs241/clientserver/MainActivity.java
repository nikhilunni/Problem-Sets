package edu.illinios.cs241.clientserver;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;


public class MainActivity extends ActionBarActivity {
    TextView mConversationView , mStatusView;
    EditText mMessageEditView, mHostText, mPortText;

    Thread mReceiverThread;

    // Verify the semester is correct
    // Verify this is your CS241 VM
    public static String SERVER_ADDR = "sp15-cs241-137.cs.illinois.edu";
    public static String SERVER_PORT = "123";

    static final SimpleDateFormat SDF = new SimpleDateFormat("hh:mm:ss");
    static final String[] EMPTY = {"!!!","/* */","The 5th","ROLF",":-)", ";-)","LOL","Meme"};

    static final String TAG = "MainActivity";
    static {
        System.loadLibrary("ndkModule");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mConversationView = (TextView) findViewById(R.id.conversation);
        mMessageEditView  = (EditText) findViewById(R.id.input_message);
        mStatusView = (TextView) findViewById(R.id.status_text);
        mHostText =(EditText) findViewById(R.id.host_text);
        mPortText = (EditText) findViewById(R.id.port_text);

        mHostText.setText(SERVER_ADDR);
        mPortText.setText(SERVER_PORT);
    }


    @Override
    protected void onStart() {
        super.onStart();
        Log.d(TAG,"onStart");

    }
public void connectClicked(View v) {
    String host = mHostText.getText().toString().trim();
    String port = mPortText.getText().toString().trim();
    mStatusView.setText("Server:"+host + " " + port);
    boolean success = connectToServer(host, port);
    if(!success) {
        mStatusView.append(" failed (see logcat for details)");
        return;
    }
    mStatusView.append(" connected");
    mReceiverThread = new Thread() {
        public void run() {
            while(true) {
                byte[] bytes= readNextMessage();
                if(bytes == null) break;
                String mesg = null;
                try {
                    mesg = new String(bytes,"UTF-8");
                } catch (UnsupportedEncodingException e) {
                    e.printStackTrace(); // Unlikely...
                }
                addLine(mesg);
            }
        }
    };
    mReceiverThread.start();
}

    @Override
    protected void onStop() {
        super.onStop();
        Log.d(TAG,"onStop");
        closeConnection();
        Log.d(TAG,"Waiting for receiver thread to finish");
        try { if(mReceiverThread != null) mReceiverThread.join(1000); }
        catch(InterruptedException ignored) {}
        Log.d(TAG, "Receiver thread finished");

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

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

    public void addLine(final String message) {
        final String when = SDF.format( new java.util.Date() );
        Runnable r = new Runnable() {
            public void run() {
                mConversationView.append(when + ": "+ message + "\n");
            }
        };
        mConversationView.post(r); // run on UI thread
    }

    // referenced in onClick in activity_main.xml
    public void sendMessageClicked(View btn) {
        String text = mMessageEditView.getText().toString().trim();
        if(text.length() == 0 )
            text = EMPTY[ (int)(Math.random() * EMPTY.length)];

        mConversationView.append("Sending <"+text+">\n");

        sendMessage(text);
        mMessageEditView.setText("");
    }




    public native void sendMessage(String message);
    public native byte[] readNextMessage();

    public native boolean connectToServer(String node, String service);
    public native void closeConnection();
}
