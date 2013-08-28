package ru.suvitruf.androidndk.tutorial5;


import android.os.Bundle;
import android.app.Activity;
import android.content.res.AssetManager;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	static {
		System.loadLibrary("AndroidNDK");    
	}
	
	native public void writeToFile(String str);
	native public void readFromFile();
	native public void initNDK(String mng);
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		
		this.initNDK(this.getFilesDir().getAbsolutePath());
		
		((Button) findViewById(R.id.writeStringBtn)).setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				writeToFile(((TextView) findViewById(R.id.text)).getText().toString());
			}
			
		});
		
	
		return true;
	}

}
