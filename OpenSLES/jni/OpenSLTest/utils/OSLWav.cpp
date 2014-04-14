#include "OSLWav.h"
#include <assert.h>
//OSLWav::OSLWav():OSLSound()
//{
//
//}

OSLWav::OSLWav(OSLContext * context, PlayerType playerType):OSLSound(context, playerType){

}
OSLWav::OSLWav( OSLContext * context,PlayerType playerType, char * path):OSLSound(context,playerType){
	load(path);
}
OSLWav::~OSLWav(){
	free(buf);
}
void OSLWav::load(char* filename) {

	strcpy(this->filename, filename);

//	LOGD("filename = %s",this->filename);
	// if set Player Buffer, than load audio data to PCM buffer
	if(playerType == BUFFER){

		buf = readWAVFull(mgr, &header);
		this->LogHeaders();
		dataSize = header.dataSize;
	}



}

AAsset* OSLWav::openFile(char * path){

	char fname[80];
	strcpy(fname, "");
	strcat(fname, path);
	//LOGI("%s start open",fname);
	if(mgr == NULL)
		LOGE("AAssetManager null");


	//packageName = new char[17];
	AAsset* asset = AAssetManager_open(mgr, fname, AASSET_MODE_UNKNOWN);
	if (mgr == NULL) {
		LOGE("AAssetManager NULL");
		return NULL;
	}
	if (NULL == asset) {
		LOGE("_ASSET_NOT_FOUND_ %s", fname);
		//__android_log_write(ANDROID_LOG_ERROR, "MyNative", "_ASSET_NOT_FOUND_");
		return NULL;
	}
	//LOGI("%s opened",fname);
	/*long size = AAsset_getLength(asset);
	 char* buffer = (char*) malloc (sizeof(char)*size);
	 AAsset_read (asset,buffer,size);
	 __android_log_print(ANDROID_LOG_ERROR, "MyNative", buffer);
	 free(buffer);*/

	return asset;
}
char* OSLWav::readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header){
	char* buffer = 0;
	AAsset * file = openFile(filename);
	//FILE* file = fopen(filename,"rb");
	if (!file) {
		LOGE("no file %s in readWAV",filename);
		return 0;
	}
	//char  str_n[30];

	char extra[2];
	// sometimes, WAV files have failed headers O_o
	int res = AAsset_read (file,header,sizeof(BasicWAVEHeader));
	// so, check it
	if(!strstr(header->data, "data")){

		AAsset_read (file,extra,2);
		header->dataSize = AAsset_getLength(file) - sizeof(BasicWAVEHeader)-2;
	}

	if(res){
		//these things *must* be valid with this basic header
		// but...
		/*if (!(
			memcmp("RIFF",header->riff,4) ||
			memcmp("WAVE",header->wave,4) ||
			memcmp("fmt ",header->fmt,4)  ||
			memcmp("data",header->data,4)
		))*/{
			//LOGI("data size = %u", header->dataSize);
			buffer = (char*)malloc(header->dataSize);
			if (buffer){
				//LOGI("	if (buffer){ inside");
				//if (fread(buffer,header->dataSize,1,file)){
				//if(AAsset_read (file,&header->dataSize,1)){
				//if(AAsset_read (file,buffer,1)){
				res = AAsset_read (file,buffer,header->dataSize);
				if(res){
					AAsset_close(file);
					return buffer;
				}
				free(buffer);
			}
		}
	}
	if(file)
		AAsset_close(file);
	return 0;
}

void OSLWav::getFormat(){

}





void OSLWav::LogHeaders(){
	LOGI("dataSize = %i ",header.dataSize);
	LOGI("bitsPerSample = %i ",header.bitsPerSample);
	LOGI("bytesPerSec = %i ",header.bytesPerSec);
	LOGI("samplesPerSec = %i ",header.samplesPerSec);
	LOGI("fmtSize = %i ",header.fmtSize);
	LOGI("riffSize = %i ",	header.riffSize);
	LOGI("channels = %i ",	header.channels);
}




char * OSLWav::getBuffer(){
	return buf;
}
long OSLWav::getSize(){
	return dataSize;
}
