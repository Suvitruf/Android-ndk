#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __ANDROID__
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <def.h>
#endif


class AAssetFile{
private:
	char * fileName;
#ifdef __ANDROID__
	AAsset* file;
	AAssetManager *mgr;
#else
	FILE * file;
#endif
	AAssetFile(){}
	public:


#ifdef __ANDROID__
	AAsset * getFile();
	AAssetFile(AAssetManager *mgr, char * fileName);

	int read(void* buf, size_t size, size_t count);
	void close(){LOGI("file %s closed", fileName);AAsset_close(file);}
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
