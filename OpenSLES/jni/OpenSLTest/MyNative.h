#include <trace.h>
#include <jni.h>


//char  MyStr[80];


extern "C" {
JNIEXPORT void JNICALL Java_ru_suvitruf_opensles_MainActivity_loadAudio(JNIEnv *pEnv, jobject pThis, jobject pNativeCallListener, jobject assetManager);


JNIEXPORT void JNICALL Java_ru_suvitruf_opensles_MainActivity_destroyObjects(JNIEnv *pEnv, jobject pThis);
JNIEXPORT void JNICALL Java_ru_suvitruf_opensles_MainActivity_play(JNIEnv *pEnv, jobject pThis);
JNIEXPORT void JNICALL Java_ru_suvitruf_opensles_MainActivity_play2(JNIEnv *pEnv, jobject pThis);
//JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial4_MainActivity_playOGG(JNIEnv *pEnv, jobject pThis);

}
/*class NativeCallListener {
public:

	NativeCallListener(JNIEnv* pJniEnv, jobject pWrapperInstance);
	NativeCallListener() {}
	//апуск таймера

	//send value to Java
    void sendLog(jobject log);
    //cleaning resources
    void destroy();

	~NativeCallListener(){
		destroy();
	}

	//loading audio
	void loadAudio();
	//void play();
	//void playOGG();
	//ALCdevice* device;
	//ALCcontext* context;
private:
	JNIEnv* getJniEnv();


	jmethodID sendLogID;
	jobject mObjectRef;
	JavaVM* mJVM;


	//ALuint soundWAV;
	//ALuint soundOGG;
	void load();
	void clean();

};

extern NativeCallListener listener;*/
//extern AAssetManager *mgr;
