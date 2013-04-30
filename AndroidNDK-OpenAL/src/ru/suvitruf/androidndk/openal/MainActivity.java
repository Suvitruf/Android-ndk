package ru.suvitruf.androidndk.openal;

import ru.suvitruf.androidndk.openal.R;
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
import android.widget.ListView;
import android.widget.TextView;

public class MainActivity extends Activity implements NativeCalls {
	static {
		System.loadLibrary("AndroidNDK");  
	}
	//загрузка ресурсов
	native public void loadAudio(NativeCalls nativeCallListener, AssetManager mng);
	//очистка
	native public void destroyObjects();
	//играем WAV
	native public void play(); 
	protected Handler handler = new Handler()
    {  
    	 @Override
         public void handleMessage(Message msg) {
    		 showResult(msg.getData().getString("result"));   		 
    	 }
    };
	
    
    public void showResult(String result){
    	((TextView) findViewById(R.id.log)).
    	setText(((TextView) findViewById(R.id.log)).getText()+result+"\n");
    
    }
	
    //отобразить количество прочитаных байт
	@Override 
	public void sendLog(String result){
		Message msg = new Message();
		Bundle data = new Bundle();
		data.putString("result", result);
		msg.setData(data);
				
		handler.sendMessage(msg);
	}
	Thread process;
	Context context;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		//makeNativeCall(this);
		context = this;
		process = new Thread(new MyRunnable(this));
		process.start();
		((Button) findViewById(R.id.playButton)).setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				if(process != null)
					process.interrupt();
				
				new Thread(new MyRunnablePlay(context)).start();
				//process.start();
				//play();
				
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

}

class MyRunnable implements Runnable {
	MainActivity activity;
	public MyRunnable(Context activity){
		this.activity = (MainActivity)activity;
	}
	 public void run() {
		 activity.loadAudio(activity, activity.getResources().getAssets());
	 }
}

class MyRunnablePlay implements Runnable {
	MainActivity activity;
	public MyRunnablePlay(Context activity){
		this.activity = (MainActivity)activity;
	}
	 public void run() {
		 activity.play();
	 }
}
