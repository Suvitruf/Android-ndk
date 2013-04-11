#include <MyNative.h>
#include <sys/time.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//struct timeval currentTime;
//struct timeval oldTime;

NativeCallListener listener;

/*
void NativeCallListener::resumeTimer(){

}*/
void NativeCallListener::stopTimer(){
	timerOn = false;
	LOGI("stoptimer");
}
void NativeCallListener::startTimer(){
	threadCount++;
	timerOn = true;
	//timerOn = true;
	LOGI("Start Timer");
	//timeLeft = 0;
	while (timerOn) {
		sleep(1);
		if(threadCount >1){
			--threadCount;
			return;
		}
		timeLeft++;
		LOGI("timeLeft %i",timeLeft);
		//LOGI("tcount %i", 	threadCount);
		//sendTime(timeLeft);
	}

	//resumeTimer();
}
void NativeCallListener::destroy(){
	timerOn = false;
	//LOGI("~NativeCallListener");
	//getJniEnv()->DeleteLocalRef(mObjectRef);
	//mObjectRef = NULL;
}

NativeCallListener::NativeCallListener(JNIEnv* pJniEnv, jobject pWrappedInstance) {
	pJniEnv->GetJavaVM(&mJVM);
	mObjectRef = pJniEnv->NewGlobalRef(pWrappedInstance);
	jclass cl = pJniEnv->GetObjectClass(pWrappedInstance);
	sendTimeID = pJniEnv->GetMethodID(cl, "sendTime", "(I)V");
	timeLeft = 0;
	timerOn = false;
	threadCount = 0;
}

JNIEnv* NativeCallListener::getJniEnv() {
	JavaVMAttachArgs attachArgs;
	attachArgs.version = JNI_VERSION_1_6;
	attachArgs.name = ">>>TimerThread";
	attachArgs.group = NULL;

	JNIEnv* env;
	if (mJVM->AttachCurrentThread(&env, &attachArgs) != JNI_OK)
		env = NULL;


	return env;
}

void NativeCallListener::sendTime(int time) {
	JNIEnv* jniEnv = getJniEnv();
	jniEnv->CallIntMethod(mObjectRef, sendTimeID, time);

}


JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_nativeCall(JNIEnv *pEnv, jobject pThis, jobject pNativeCallListener){
	listener = NativeCallListener(pEnv, pNativeCallListener);
	LOGI("NativeCall");
}
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_startTimer(JNIEnv *pEnv, jobject pThis) {


	//if(listener.timeLeft ==0)
	listener.startTimer();
	//else listener.resumeTimer();

}


JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_stopTimer(JNIEnv *pEnv, jobject pThis){
	listener.stopTimer();
	listener.threadCount = 0;
}
/*
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_resumeTimer(JNIEnv *pEnv, jobject pThis){
	if(listener.timeLeft != 0)
		listener.resumeTimer();
}
*/

JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial2_MainActivity_destroyObjects(JNIEnv *pEnv, jobject pThis){
	listener.destroy();
}
