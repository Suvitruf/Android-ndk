package ru.suvitruf.androidndk.tutorial2;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements NativeCalls {
	// Загрузка модуля «AndroidNDK» — нативной библиотеки, в которой реализованы методы. 
	// Название этого модуля задается в файле Android.mk.
	static {
		System.loadLibrary("AndroidNDK");
	}
	native void destroyObjects();
	native void startTimer();
	native void stopTimer();
	public Context context;
	native void nativeCall(NativeCalls nativeCallListener);

	
	public static String TAG = "androidndk";
	protected Handler handler = new Handler()
    {
    	 @Override
         public void handleMessage(Message msg) {
    		 setTime(msg.what);
    	 }
    };
	
    public void setTime(int time){
    	Log.i("androidndk",Long.toString(time));
		((TextView)findViewById(R.id.timerText)).setText(Long.toString(time));
    }
	
	@Override 
	public void sendTime(int time){		
		handler.sendEmptyMessage(time);
	}
	Thread process;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.context = this;
		setContentView(R.layout.activity_main);
		nativeCall(this);

		
		((Button) findViewById(R.id.startTimerButton)).setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				
			
				if(process != null){
					stopTimer();
					process.interrupt();
				}
				process = new Thread(new MyRunnable(context));				
				process.start();
				
			}
		});
		
		
		
	}
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	protected void onDestroy(){
    	super.onDestroy();
    	destroyObjects();

    }
	
	@Override
	protected void onStop(){
		super.onStop();		
		
		if(process != null){
			process.interrupt();
			this.stopTimer();
		}

	}
	
	@Override
	protected void onStart(){
		super.onStart();
	}

	
	

}

class MyRunnable implements Runnable {
	MainActivity activity;

	public MyRunnable(Context activity){
		this.activity = (MainActivity)activity;
	}
	
	public void run() {		
		activity.startTimer(); 
	}
	 
	 
}


