#include <def.h>
#include <jni.h>

char  MyStr[80];


extern "C" {
    JNIEXPORT void Java_ru_suvitruf_androidndk_tutorial1_AndroidNDK_SetString(JNIEnv * env, jobject obj, jstring str);
    JNIEXPORT void Java_ru_suvitruf_androidndk_tutorial1_AndroidNDK_ChangeString(JNIEnv * env, jobject obj);
    JNIEXPORT jstring Java_ru_suvitruf_androidndk_tutorial1_AndroidNDK_GetString(JNIEnv * env, jobject obj);
}
