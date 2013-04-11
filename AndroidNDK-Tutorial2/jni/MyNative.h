#include <def.h>
#include <jni.h>




extern "C" {
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_nativeCall(JNIEnv *pEnv, jobject pThis, jobject pNativeCallListener);
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_startTimer(JNIEnv *pEnv, jobject pThis);
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_destroyObjects(JNIEnv *pEnv, jobject pThis);
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_stopTimer(JNIEnv *pEnv, jobject pThis);
//JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_resumeTimer(JNIEnv *pEnv, jobject pThis);
}

class NativeCallListener {
public:
	int threadCount;
	//сколько прошло времени
	int timeLeft;
    //активен ли таймер
	bool timerOn;
	NativeCallListener(JNIEnv* pJniEnv, jobject pWrapperInstance);
	NativeCallListener() {}
	//запуск таймера
	void startTimer();
	//тормозим таймер
	//void resumeTimer();
	//стопаем таймер
	void stopTimer();
	//передать значение в Java метод
    void sendTime(int time);
    //отключаем таймер
    void destroy();
	~NativeCallListener(){}
private:
	JNIEnv* getJniEnv();

    //ссылка на метод
	jmethodID sendTimeID;
	//ссылка на объект
	jobject mObjectRef;
	JavaVM* mJVM;
};

extern NativeCallListener listener;
