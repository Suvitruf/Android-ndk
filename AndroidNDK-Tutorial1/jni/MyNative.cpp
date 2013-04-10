#include <MyNative.h>


/**
* Отправка строки в native.
*/
JNIEXPORT void Java_ru_suvitruf_androidndk_tutorial1_AndroidNDK_SetString(JNIEnv * env, jobject obj, jstring str){

	jboolean isCopy;
	const char * Str;

	Str = env->GetStringUTFChars(str, &isCopy);
	strcpy(MyStr,Str);
	LOGI("string = \"%s\"",MyStr);

}

void ChangeStr(){

	strcat(MyStr," and bb.");
}

/**
 * Изменение строки.
 */
JNIEXPORT void Java_ru_suvitruf_androidndk_tutorial1_AndroidNDK_ChangeString(JNIEnv * env, jobject obj){
	ChangeStr();
	LOGI("string after change = \"%s\"",MyStr);
}

/**
 * Получение строки из native в Java.
 */
JNIEXPORT jstring Java_ru_suvitruf_androidndk_tutorial1_AndroidNDK_GetString(JNIEnv * env, jobject obj){

	LOGI("returned string = \"%s\"",MyStr);
	return env->NewStringUTF(MyStr);
}
