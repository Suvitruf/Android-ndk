#include <MyNative.h>
#include <sys/time.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
//struct timeval currentTime;
//struct timeval oldTime;

NativeCallListener listener;
AAssetManager *mgr;
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial3_MainActivity_readResources(JNIEnv *pEnv, jobject pThis, jobject pNativeCallListener, jobject assetManager) {

	listener = NativeCallListener(pEnv, pNativeCallListener);
	mgr = AAssetManager_fromJava(pEnv, assetManager);

	listener.readResources();
}

void NativeCallListener::destroy(){}

NativeCallListener::NativeCallListener(JNIEnv* pJniEnv, jobject pWrappedInstance) {
	pJniEnv->GetJavaVM(&mJVM);
	mObjectRef = pJniEnv->NewGlobalRef(pWrappedInstance);
	jclass cl = pJniEnv->GetObjectClass(pWrappedInstance);
	sendResultID = pJniEnv->GetMethodID(cl, "sendResult", "(I)V");

}

void NativeCallListener::readResources(){
	char *  name = new char[64];
	strcpy(name, "111.txt");
	AAssetFile f = AAssetFile(mgr, name);
	char buf[f.size()+1];
	int count = f.read(&buf,f.size(),1);
	buf[f.size()] = '\0';
	LOGI("file read : %s ",buf);
	LOGI("read count = %i",count);
	LOGI("file size = %i ",f.size());
	LOGI("size of buf= %i ",sizeof(buf));
	sendResult( count);
	f.close();
}

JNIEnv* NativeCallListener::getJniEnv() {
	JavaVMAttachArgs attachArgs;
	attachArgs.version = JNI_VERSION_1_6;
	attachArgs.name = ">>>TimerThread";
	attachArgs.group = NULL;

	JNIEnv* env;
	if (mJVM->AttachCurrentThread(&env, &attachArgs) != JNI_OK) {
		env = NULL;
	}

	return env;
}

void NativeCallListener::sendResult(int result) {
	JNIEnv* jniEnv = getJniEnv();
	LOGI(" result = %i", result);
	jniEnv->CallVoidMethod(mObjectRef, sendResultID, result);

}

