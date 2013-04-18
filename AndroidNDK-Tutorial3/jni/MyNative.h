#include <def.h>
#include <jni.h>
#include "AAssetFile.h"
char  MyStr[80];


extern "C" {
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial3_MainActivity_readResources(JNIEnv *pEnv, jobject pThis, jobject pNativeCallListener, jobject assetManager);


JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial3_AndroidNDK_destroyObjects(JNIEnv *pEnv, jobject pThis);

}
class NativeCallListener {
public:
	//сколько прошло времени
	//int timeLeft;
    //активен ли таймер
	//bool timerOn;
	NativeCallListener(JNIEnv* pJniEnv, jobject pWrapperInstance);
	NativeCallListener() {}
	//апуск таймера
	//void startTimer();
	//передать значение в Java метод
    void sendResult(int result);
    //отключаем таймер
    void destroy();
	~NativeCallListener(){
		//LOGI("~NativeCallListener");

	}
	void readResources();
private:
	JNIEnv* getJniEnv();

    //ссылка на метод
	jmethodID sendResultID;
	//ссылка на объект
	jobject mObjectRef;
	JavaVM* mJVM;
};

extern NativeCallListener listener;
