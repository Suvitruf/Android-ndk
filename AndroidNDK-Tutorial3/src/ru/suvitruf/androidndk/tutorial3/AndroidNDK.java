package ru.suvitruf.androidndk.tutorial3;

public class AndroidNDK {
	
	// Загрузка модуля «AndroidNDK» — нативной библиотеки, в которой реализованы методы. 
	// Название этого модуля задается в файле Android.mk.
	static {
		System.loadLibrary("AndroidNDK");
	}
	
	//public static native void destroyObjects(); 
}
 