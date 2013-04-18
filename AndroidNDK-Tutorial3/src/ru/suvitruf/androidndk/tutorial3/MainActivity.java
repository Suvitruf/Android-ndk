package ru.suvitruf.androidndk.tutorial3;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements NativeCalls {
	static {
		System.loadLibrary("AndroidNDK");
	}
	
	
	protected Handler handler = new Handler()
    { 
    	 @Override
         public void handleMessage(Message msg) {
    		 //setTime(msg.what);
    		 showResult(msg.getData().getInt("result"));
    		 
    	 }
    };
	
    
    public void showResult(int result){
    	Log.i("androidndk",Integer.toString(result));
		((TextView)findViewById(R.id.timerText)).setText("Прочитано: "+Integer.toString(result));
    }
	
    //отобразить количество прочитаных байт
	@Override 
	public void sendResult(int result){
		Message msg = new Message();
		Bundle data = new Bundle();
		data.putInt("result", result);
		msg.setData(data);
				
		handler.sendMessage(msg);
	}
	Thread process;
	
	//загрузка ресурсов
	native public void readResources(NativeCalls nativeCallListener, AssetManager mng);
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		//makeNativeCall(this);
		process = new Thread(new MyRunnable(this));
		((Button) findViewById(R.id.startTimerButton)).setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				
				process.start();
			}
		});
		
		/*((Button) findViewById(R.id.setTextButton)).setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				AndroidNDK.SetString(((TextView)findViewById(R.id.originalET)).getText().toString());
			}
		});
		
		((Button) findViewById(R.id.changeTextButton)).setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				AndroidNDK.ChangeString();
			}
		});
		
		((Button) findViewById(R.id.getTextButton)).setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				String str = AndroidNDK.GetString();
				((TextView)findViewById(R.id.afterChangeET)).setText(str);
			}
		});*/
		
		
	}
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	protected void onDestroy(){
    	super.onDestroy();
    	//AndroidNDK.destroyObjects();
    	//Log.i("androidndk","onDestroy");
    }

}

class MyRunnable implements Runnable {
	MainActivity activity;
	public MyRunnable(MainActivity activity){
		this.activity = activity;
	}
	 public void run() {
		 activity.readResources(activity, activity.getResources().getAssets());
	 }
}
