#include <MyNative.h>
#include <sys/time.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>

//struct timeval currentTime;
//struct timeval oldTime;


//AAssetManager *mgr;
const char * internalStoragePath;
JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial5_MainActivity_initNDK(JNIEnv *pEnv, jobject pThis, jstring path) {

	internalStoragePath =pEnv->GetStringUTFChars(path, 0);

	//LOGI("internalStoragePath = %s", internalStoragePath);
	//mgr = AAssetManager_fromJava(pEnv, assetManager);

	struct stat sb;
	int32_t res = stat(internalStoragePath, &sb);
	if (0 == res && sb.st_mode && S_IFDIR){
		LOGD("'%s' dir already in app's internal data storage.",internalStoragePath);
	}
	else if (ENOENT == errno){
	        res = mkdir(internalStoragePath, 0770);
	}


}


JNIEXPORT void JNICALL Java_ru_suvitruf_androidndk_tutorial5_MainActivity_writeToFile(JNIEnv *pEnv, jobject pThis, jstring str){
	const char * text =pEnv->GetStringUTFChars(str, 0);

	LOGI("string = %s", text);
	char fName[64];
	strcpy(fName,internalStoragePath);
	strcat(fName,"/myfile.txt");
	LOGI("fname = %s", fName);
	FILE* f= fopen(fName, "w+");
	fwrite(text, sizeof(text), sizeof(text), f);
	fclose(f);
}
