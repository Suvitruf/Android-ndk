#include <MyNative.h>
#include <sys/time.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "OSLContext.h"
#include "OSLSound.h"
#include "OSLWav.h"
#include "OSLMp3.h"
//struct timeval currentTime;
//struct timeval oldTime;

AAssetManager *mgr;


OSLContext * context;
OSLSound * sound1;
OSLSound * sound2;






JNIEXPORT void JNICALL Java_ru_suvitruf_opensles_MainActivity_loadAudio(JNIEnv *pEnv, jobject pThis, jobject pNativeCallListener, jobject assetManager) {

	mgr = AAssetManager_fromJava(pEnv, assetManager);

	context = new OSLContext(mgr);
	sound1 = new OSLWav(context);
	sound1->load("ваш_файл.wav");
	sound1->setVolume(1.0F);

	sound2 = new OSLMp3(context);
	sound2->load("ваш_файл.mp3");
//	sound2->setLoop(true);
	sound2->setVolume(1.0F);
}

JNIEXPORT void JNICALL Java_ru_suvitruf_opensles_MainActivity_destroyObjects(JNIEnv *pEnv, jobject pThis){

}
JNIEXPORT void JNICALL Java_ru_suvitruf_opensles_MainActivity_play(JNIEnv *pEnv, jobject pThis){
	if(sound1->isPlaying())
		sound1->stop();
	else
		sound1->play();
}
JNIEXPORT void JNICALL Java_ru_suvitruf_opensles_MainActivity_play2(JNIEnv *pEnv, jobject pThis){
//	LOGD("hm?");
	if(sound2->isPlaying())
			sound2->stop();
		else
			sound2->play();
}
