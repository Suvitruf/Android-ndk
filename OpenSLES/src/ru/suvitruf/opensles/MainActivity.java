package ru.suvitruf.opensles;

import ru.suvitruf.opensles.R;
import android.os.Bundle;
import android.os.Message;
import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity implements NativeCalls  {
	static {
		System.loadLibrary("OpenSL");  
	} 
	 
	//�������� ��������
	native public void loadAudio(NativeCalls nativeCallListener, AssetManager mng);
	//�������
	native public void destroyObjects();
	//������ WAV
	native public void play();
	native public void play2();
	//���������� ���������� ���������� ����
	
	@Override 
	public void sendLog(String result){
		
	}
	Thread process;
	Context context;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		context = this;
		loadAudio(this, getResources().getAssets());
//		process = new Thread(new MyRunnable(this));
//		process.start();
		((Button) findViewById(R.id.playButton)).setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
//				if(process != null)
//					process.interrupt();
//				
//				new Thread(new MyRunnablePlay(context)).start();
//				
				play();
			}
		});
		((Button) findViewById(R.id.playButton2)).setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
//				if(process != null)
//					process.interrupt();
//				
//				new Thread(new MyRunnablePlay(context)).start();
//				
				play2();
			}
		});
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	
	class MyRunnable implements Runnable {
		MainActivity activity;

		public MyRunnable(Context activity) {
			this.activity = (MainActivity) activity;
		}

		public void run() {
			activity.loadAudio(activity, activity.getResources().getAssets());
		}
	}

	class MyRunnablePlay implements Runnable {
		MainActivity activity;

		public MyRunnablePlay(Context activity) {
			this.activity = (MainActivity) activity;
		}

		public void run() {
			activity.play();
		}
	}

}
