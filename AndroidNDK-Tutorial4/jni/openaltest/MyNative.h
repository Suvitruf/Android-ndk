#include <trace.h>
#include <jni.h>
//#include "AAssetFile.h"
#include "OALSound.h"
char  MyStr[80];


extern "C" {
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial4_MainActivity_loadAudio(JNIEnv *pEnv, jobject pThis, jobject pNativeCallListener, jobject assetManager);


JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial4_MainActivity_destroyObjects(JNIEnv *pEnv, jobject pThis);
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial4_MainActivity_play(JNIEnv *pEnv, jobject pThis);
//JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial4_MainActivity_playOGG(JNIEnv *pEnv, jobject pThis);

}
class NativeCallListener {
public:

	NativeCallListener(JNIEnv* pJniEnv, jobject pWrapperInstance);
	NativeCallListener() {}
	//апуск таймера

	//передать значение в Java метод
    void sendLog(jobject log);
    //очистка всех ресурсов
    void destroy();
	~NativeCallListener(){

	}
	void loadAudio();
	//void play();
	//void playOGG();
	ALCdevice* device;
	ALCcontext* context;
private:
	JNIEnv* getJniEnv();

    //ссылка на метод
	jmethodID sendLogID;
	//ссылка на объект
	jobject mObjectRef;
	JavaVM* mJVM;


	ALuint soundWAV;
	ALuint soundOGG;
	void load();
	void clean();

};

extern NativeCallListener listener;
//extern AAssetManager *mgr;
