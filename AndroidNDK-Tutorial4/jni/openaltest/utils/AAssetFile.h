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
	AAssetFile(){}

#ifdef __ANDROID__
	bool null(){
		return !file;
	}
	AAsset * getFile();
	AAssetFile(AAssetManager *mgr, const char* fileName);

	int read(void* buf, size_t size, size_t count);
	void close(){/*LOGI("file %s closed", fileName);*/AAsset_close(file);}
	~AAssetFile(){ }
	off_t size() { return AAsset_getLength (file); }
#else
	AAssetFile(char * fileName);
	size_t	 fread(void *buff, size_t size, size_t count);
	FILE * getFile();
	void close(){fclose(file);}
	~AAssetFile(){}
#endif


};
