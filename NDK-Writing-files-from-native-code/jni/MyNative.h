#include <trace.h>
#include <jni.h>

char  MyStr[80];


extern "C" {
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial5_MainActivity_initNDK(JNIEnv *pEnv, jobject pThis,  jstring assetManager);

JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial5_MainActivity_writeToFile(JNIEnv *pEnv, jobject pThis, jstring str);

}

