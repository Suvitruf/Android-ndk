#include <MyNative.h>
#include <sys/time.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "OALContext.h"
//struct timeval currentTime;
//struct timeval oldTime;

NativeCallListener listener;
AAssetManager *mgr;
OALSound * sound;
OALContext * oalContext;


void NativeCallListener::destroy(){
	clean();
}
/*JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial4_MainActivity_playOGG(JNIEnv *pEnv, jobject pThis){
	listener.playOGG();
}*/
NativeCallListener::NativeCallListener(JNIEnv* pJniEnv, jobject pWrappedInstance) {
	pJniEnv->GetJavaVM(&mJVM);
	mObjectRef = pJniEnv->NewGlobalRef(pWrappedInstance);
	jclass cl = pJniEnv->GetObjectClass(pWrappedInstance);
	sendLogID = pJniEnv->GetMethodID(cl, "sendLog", "(Ljava/lang/String;)V");

}
/*void NativeCallListener::playOGG(){

}*/
void play(){
	if(sound->isPlaying())
		sound->stop();
	else
		sound->play();
	//sound->setVolume(1.0);
	/*

	 ALuint source = 0;
	 alGenSources(1, &source );
	 alSourcei(source, AL_BUFFER,soundWAV);


	 alSourcePlay(source);

	 int sourceState = AL_PLAYING;
	 do {
		 alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
	 } while(sourceState == AL_PLAYING);


	 alDeleteSources(1, &source);

	*/
	 //sendLog(getJniEnv()->NewStringUTF("playing complete"));
}
void NativeCallListener::clean(){
	delete oalContext;
	delete sound;
	/*alDeleteBuffers(1, &soundWAV);

	alcMakeContextCurrent(0);
	alcDestroyContext(context);
	alcCloseDevice(device);*/
}
/*void NativeCallListener:: init(){
	device = 0;
	ALCcontext* context = 0;
	const ALint context_attribs[] = { ALC_FREQUENCY, 22050, 0 };

	//инициализация
	device = alcOpenDevice(0);
	context = alcCreateContext(device, context_attribs);
	alcMakeContextCurrent(context);





}*/


void NativeCallListener:: load(){
	oalContext = new OALContext();
	//sound = new OALOgg(false);
	//sound = new OALWav(true);
	//sound = new OALWav(mgr,"audio/industrial_suspense1.wav", false);
	sound = new OALWav(mgr,"audio/industrial_suspense1.wav", true);
	//sound = new OALOgg(mgr, "audio/Katatonia - Deadhouse_(piano version).ogg", true);
	//sound = new OALOgg(mgr, "audio/Katatonia - Deadhouse_(piano version).ogg", false);
	//char *  fileName = new char[64];

	//strcpy(fileName, "audio/SnowflakePickUpV_3.wav");
	//strcpy(fileName, "audio/Katatonia - Deadhouse_(piano version).ogg");
	//strcpy(fileName, "audio/industrial_suspense1.wav");
	//sound->load(mgr,fileName);
	/*
	BasicWAVEHeader header;
	char* data = readWAV(mgr, fileName,&header);
	soundWAV = createBufferFromWave(data, header);*/

}
void NativeCallListener::loadAudio(){
	//init();
	load();

	sendLog(getJniEnv()->NewStringUTF("load complete!"));

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

void NativeCallListener::sendLog(jobject log) {
	JNIEnv* jniEnv = getJniEnv();
	jniEnv->CallIntMethod(mObjectRef, sendLogID, log);

}


JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_openal_MainActivity_loadAudio(JNIEnv *pEnv, jobject pThis, jobject pNativeCallListener, jobject assetManager) {

	listener = NativeCallListener(pEnv, pNativeCallListener);
	mgr = AAssetManager_fromJava(pEnv, assetManager);
	listener.loadAudio();
}

JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_openal_MainActivity_destroyObjects(JNIEnv *pEnv, jobject pThis){
	listener.destroy();
}
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_openal_MainActivity_play(JNIEnv *pEnv, jobject pThis){
	play();
}
