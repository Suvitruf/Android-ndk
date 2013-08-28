#include "AAssetFile.h"

#ifdef __ANDROID__
AAsset * AAssetFile:: getFile(){
	return file;
}

AAssetFile::AAssetFile(AAssetManager *mgr, const char* fileName){
	this->mgr = mgr;
	this->fileName = fileName;

	file = AAssetManager_open(mgr, fileName,  AASSET_MODE_STREAMING );
	if(mgr == NULL)
		LOGE("AAssetManager NULL");

	if (file == NULL)
		LOGE("_ASSET_NOT_FOUND_ %s",fileName);

}

off_t AAssetFile::seek(off_t offset, int whence){
	/*LOGI("seek offset %i whence %i",  offset, whence);
	LOGI("sizeof = %i",sizeof(file));
	off_t  res = -1;
	if(this->null())
		LOGI("error ='/");
	if(this->size() != 0)
	//try{
		res = AAsset_seek(file,offset,whence);
	if(res == -1)
		LOGI("error T_T");
	//}
	//catch(...){
	else{
		LOGI("error =/");
		this->close();
		file = AAssetManager_open(mgr, fileName,  AASSET_MODE_STREAMING );
		res= AAsset_seek(file,offset,whence);
	}
	return res ;*/
	return AAsset_seek(file,offset,whence);
}
int AAssetFile::read(void* buf, size_t size, size_t count){
	return AAsset_read (file,buf,size*count);
}

#else
AAssetFile::AAssetFile(char * fileName){
size_t	 AAssetFile::fread(void *buff, size_t size, size_t count){
	return fread(&buff, size, count, file);
}
FILE * AAssetFile::getFile(){
	return file;
}
#endif
