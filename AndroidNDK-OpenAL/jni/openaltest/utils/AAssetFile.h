//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>

#ifdef __ANDROID__
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <trace.h>
#endif


class AAssetFile{
private:
	const char* fileName;
#ifdef __ANDROID__
	AAsset* file;
	AAssetManager *mgr;
#else
	FILE * file;
#endif

	public:
	/*AAssetFile(){

	}*/

#ifdef __ANDROID__
	AAssetManager * getManager(){
		return mgr;
	}
	bool null(){
		return !file || file == NULL|| file == 0;
	}
	//void  Log(){LOGI("lol?");}

	AAsset * getFile();
	AAssetFile(AAssetManager *mgr, const char* fileName);
	off_t seek(off_t offset, int whence);
	int read(void* buf, size_t size, size_t count);
	void close(){
		//LOGI("f %s closed", fileName);
		AAsset_close(file);
	}
	~AAssetFile(){
		//LOGI("~AAssetFile()");
		if(fileName)
			delete fileName;
	}
	off_t size() {
		//LOGI("fsize = %i",AAsset_getLength (file));
		return AAsset_getLength (file);
	}
#else
	AAssetFile(char * fileName);
	size_t	 fread(void *buff, size_t size, size_t count);
	FILE * getFile();
	void close(){fclose(file);}
	~AAssetFile(){}
#endif


};
