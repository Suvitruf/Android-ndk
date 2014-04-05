#include "OSLWav.h"
#include <assert.h>
//OSLWav::OSLWav():OSLSound()
//{
//
//}

OSLWav::OSLWav(OSLContext * context):OSLSound(context){

}
OSLWav::OSLWav( OSLContext * context, char * path):OSLSound(context){
	load(path);
}
OSLWav::~OSLWav(){

}

//void OSLWav::setVolume(float volume){
//
//	context->getFreePlayer()->setVolume(volume);
//}
//
//float OSLWav::getVolume(){
//	return context->getFreePlayer()->getVolume();
//
//}
//bool OSLWav::isPlaying(){
//	LOGD("isPlaying");
//
//}
//void OSLWav::stop(){
//	LOGD("stop");
//	SLresult result;
//	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_STOPPED);
//	assert(SL_RESULT_SUCCESS == result);
//}
//void OSLWav::pause(){
//	LOGD("pause");
//	SLresult result;
//	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_PAUSED);
//	assert(SL_RESULT_SUCCESS == result);
//}
//void OSLWav::play(){
//	LOGD("play");
//	SLresult result;
//	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
//	 assert(SL_RESULT_SUCCESS == result);
//
//
//}
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
	//AAsset_read (asset,&halfWallSize,sizeof(halfWallSize));
	//AAsset_read (file,&header,sizeof(BasicWAVEHeader));
	//if (fread(header,sizeof(BasicWAVEHeader),1,file)){
	int res = AAsset_read (file,header,sizeof(BasicWAVEHeader));
	if(!strstr(header->data, "data")){

		AAsset_read (file,extra,2);
		header->dataSize = AAsset_getLength(file) - sizeof(BasicWAVEHeader)-2;
	}
//	else
//		LOGD("good %s",filename);
//	if(!strstr(header->data, "data")){
//		AAsset_close(file);
//		LOGD("bad");
//		file = MyFileOpen(filename);
//		BadBasicWAVEHeader  badHeader;
////		LOGD("sizeofchar = %i",sizeof(char));
//		int res = AAsset_read (file,&badHeader,sizeof(BadBasicWAVEHeader));
//		LOGD("bad %s, %u", badHeader.data,badHeader.dataSize);
//		header->dataSize = badHeader.dataSize;
//		header->dataSize = header->channels * header->bytesPerSec/8 *header->

//	}
//	else
//		LOGD("cool %s, %u", header->data,header->dataSize);
	//LOGI("read %i bytes from %s", res,filename );
	if(res){
		//LOGI("AAsset_read %s,",filename);
		/*if (!(//these things *must* be valid with this basic header
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
					//LOGD("res = %i",res);
//					if(!strstr(header->data, "data")){
//
//						header->dataSize = res;
//					}
					AAsset_close(file);
					//fclose(file);
					return buffer;
				}
				free(buffer);
			}
		}
	}
	//fclose(file);
	AAsset_close(file);
	return 0;
}

void OSLWav::getFormat(){
//	switch (header.bitsPerSample){
//
//		}
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


void OSLWav::load(char* filename) {
//	LOGD("0");
	strcpy(this->filename, filename);
//	this->filename = filename;
	buf = readWAVFull(mgr, &header);
	this->LogHeaders();
	dataSize = header.dataSize;
//	LOGD("file = %s",filename);


	// enable whole file looping
//	result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
//	assert(SL_RESULT_SUCCESS == result);
//return;
//	SLBufferQueueItf bufferQueue;


//	result = (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
//	assert(SL_RESULT_SUCCESS == result);


//	 initBuf();
//	createBufferQueuePlayer();
//

}
//void OSLWav:: initBuf(){


//	(*bufferQueue)->Clear(bufferQueue); /*������� ������� �� ������, ���� ��� ���-�� ����. ����� ��������, ���� �������, ����� ������� ������� ���� ��������*/
//	(*bufferQueue)->Enqueue(bufferQueue, buf, header.dataSize);
//}

//void OSLWav::createBufferQueuePlayer(){
//	 SLresult result;
//
//	// configure audio source
//	SLDataLocator_AndroidSimpleBufferQueue locatorBufferQueue = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
//	SLDataFormat_PCM formatPCM = {SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_44_1,
//			SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
//			SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN};
//	SLDataSource audioSrc = {&locatorBufferQueue, &formatPCM};
//
//	// configure audio sink
//	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObj};
//	SLDataSink audioSnk = {&loc_outmix, NULL};
//
//	// create audio player
//	const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND,
//					/*SL_IID_MUTESOLO,*/ SL_IID_VOLUME};
//	const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
//					/*SL_BOOLEAN_TRUE,*/ SL_BOOLEAN_TRUE};
//	result = (*context.getEngine())->CreateAudioPlayer(context.getEngine(), &playerObj, &audioSrc, &audioSnk, 3, ids, req);
//
//	// realize the player
//	result = (*playerObj)->Realize(playerObj, SL_BOOLEAN_FALSE);
//
//	// get the play interface
//	result = (*playerObj)->GetInterface(playerObj, SL_IID_PLAY, &player);
//
//	// get the buffer queue interface
//	result = (*playerObj)->GetInterface(playerObj, SL_IID_BUFFERQUEUE, &bufferQueue);
//
//	// set the player's state to playing
//	result = (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
//
//	return result;
//}
char * OSLWav::getBuffer(){
	return buf;
}
long OSLWav::getSize(){
	return dataSize;
}
