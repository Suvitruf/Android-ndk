#include "OSLOgg.h"
#include <assert.h>
#include <string.h>


OSLOgg::OSLOgg(OSLContext * context, PlayerType playerType):OSLSound(context, playerType){
	setLoop(true);
}
OSLOgg::OSLOgg( OSLContext * context, PlayerType playerType, char * path):OSLSound(context, playerType){
	load(path);
}
OSLOgg::~OSLOgg(){
	free(buf);
}

unsigned int Min( unsigned int agr1,  unsigned int agr2){
	return (agr1 <agr2) ?agr1 : agr2;
}

void OSLOgg::load(char* filename) {

	strcpy(this->filename, filename);
//	LOGD("filename = %s, this->filename = %s",filename, this->filename);

	// if set Player Buffer, than load audio data to PCM buffer
	if(playerType == BUFFER){
		AAsset* f = openFile(filename);
		if (!f) {
				LOGE("no file %s",filename);
				throw "no file %s";
		}
		buf = 0;
		off_t length = AAsset_getLength(f);
		buf = (char*) malloc(length);
		if (buf) {
			if (AAsset_read(f,buf, length)) {

			} else {
				free(buf);
				AAsset_close(f);

				LOGE("smthng wrong with %s",filename);
				throw "smthng wrong while reading file";
	//			return;
			}
		}

//		LOGD("length = %d", length);
		this->buf =  (char *) ConvertOggToPCM(length, buf);
		if(f)
			AAsset_close(f);
	}
}


unsigned int suiCurrPos = 0;
unsigned int suiSize = 0;

static size_t read_func(void* ptr, size_t size, size_t nmemb,
		void* datasource) {
	unsigned int uiBytes = Min(suiSize - suiCurrPos,	(unsigned int) nmemb * (unsigned int) size);
	memcpy(ptr, (unsigned char*) datasource + suiCurrPos, uiBytes);
	suiCurrPos += uiBytes;
//	LOGD("suiCurrPos %d",	suiCurrPos);
	return uiBytes;
}



static int seek_func(void* datasource, ogg_int64_t offset, int whence) {
//	LOGD("seek_func");
	if (whence == SEEK_SET)
		suiCurrPos = (unsigned int) offset;
	else if (whence == SEEK_CUR)
		suiCurrPos = suiCurrPos + (unsigned int) offset;
	else if (whence == SEEK_END)
		suiCurrPos = suiSize;
	return 0;
}

static int close_func(void* datasource) {
//	LOGD("close_func");
	return 0;
}

static long tell_func(void* datasource) {
	return (long) suiCurrPos;
}
void OSLOgg::Log() {
	LOGI("vi->channels = %i", vi->channels);
	LOGI("vi->rate = %i", vi->rate);
	LOGI("vi->version = %i", vi->version);
	LOGI("uiPCMSamples = %i", uiPCMSamples);
}
void OSLOgg::getInfo(unsigned int uiOggSize, char* pvOggBuffer) {
	// replace callbacks
	ov_callbacks callbacks;
	callbacks.read_func = &read_func;
	callbacks.seek_func = &seek_func;
	callbacks.close_func = &close_func;
	callbacks.tell_func = &tell_func;

	suiCurrPos = 0;
	suiSize = uiOggSize;
	int iRet = ov_open_callbacks(pvOggBuffer, &vf, NULL, 0, callbacks);

	// header
	vi = ov_info(&vf, -1);

	uiPCMSamples = (unsigned int) ov_pcm_total(&vf, -1);

	Log();
}

void * OSLOgg::ConvertOggToPCM(unsigned int uiOggSize,	char* pvOggBuffer) {
	long iRead;

	if (suiSize == 0) {
		getInfo(uiOggSize, pvOggBuffer);
		current_section = 0;
		iRead = 0;
		uiCurrPos = 0;
	}

	void* pvPCMBuffer = malloc(uiPCMSamples * vi->channels * sizeof(short));

	// decode
	do {
		iRead = ov_read(&vf, (char*) pvPCMBuffer + uiCurrPos, 4096,&current_section);
		uiCurrPos += (unsigned int) iRead;
	} while (iRead != 0);
	size = uiCurrPos;
	free(pvOggBuffer);
	buf = (char *)pvPCMBuffer;

	return buf;

}

AAsset* OSLOgg::openFile(char * path){

	char fname[80];
	strcpy(fname, "");
	strcat(fname, path);

	if(mgr == NULL)
		LOGE("AAssetManager null");


	AAsset* asset = AAssetManager_open(mgr, fname, AASSET_MODE_BUFFER);
	if (mgr == NULL) {
		LOGE("AAssetManager NULL");
		return NULL;
	}
	if (NULL == asset) {
		LOGE("_ASSET_NOT_FOUND_ %s", fname);
		return NULL;
	}


	return asset;
}
long OSLOgg:: getSize(){
	LOGD("size = %d", size);
	return size;
}
char * OSLOgg::getBuffer(){
	return buf;
}
