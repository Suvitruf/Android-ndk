package ru.suvitruf.androidndk.tutorial1;

import ru.suvitruf.androidndk.tutorial1.R;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		((Button) findViewById(R.id.setTextButton)).setOnClickListener(new Button.OnClickListener() {
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
		});
	}
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}
