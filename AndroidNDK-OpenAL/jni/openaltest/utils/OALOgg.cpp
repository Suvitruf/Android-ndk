#include "OALOgg.h"

OALOgg::OALOgg() :
		OALSound() {
	//this->streaming = false;
}

OALOgg::OALOgg(bool streaming) :
		OALSound(streaming) {

}
OALOgg::OALOgg(AAssetManager *mgr, char * fileName, bool streaming):OALSound(streaming){
	load(mgr,fileName);
}
OALOgg::~OALOgg() {
	ov_clear(&vf);
}

unsigned int suiCurrPos = 0;
unsigned int suiSize = 0;
//unsigned char* pvOggBuffer;
static size_t read_func(void* ptr, size_t size, size_t nmemb,
		void* datasource) {
	unsigned int uiBytes = Min(suiSize - suiCurrPos,
			(unsigned int) nmemb * (unsigned int) size);
	memcpy(ptr, (unsigned char*) datasource + suiCurrPos, uiBytes);
	suiCurrPos += uiBytes;
	//
	return uiBytes;
}

static size_t read_func_streaming(void* ptr, size_t size, size_t nmemb,
		void* datasource) {

	unsigned int uiBytes = Min(suiSize - suiCurrPos,
			(unsigned int) nmemb * (unsigned int) size);
	//LOGI("sizeof = %i", sizeof(datasource));
	/*if(datasource == NULL || ((AAssetFile*)datasource)->null())
	 LOGI("null f )=");*/
	//LOGI("before  suiCurrPos = %i , suiSize %i",suiCurrPos, suiSize);
	((AAssetFile*) datasource)->seek(suiCurrPos, 0);
	//LOGI("-_- ");
	//LOGI("uiBytes = %i",uiBytes);
	((AAssetFile*) datasource)->read(ptr, uiBytes, 1);

	suiCurrPos += uiBytes;
	//LOGI("after  suiCurrPos = %i , suiSize %i",suiCurrPos, suiSize);
	return uiBytes;
}

static int seek_func(void* datasource, ogg_int64_t offset, int whence) {
	if (whence == SEEK_SET)
		suiCurrPos = (unsigned int) offset;
	else if (whence == SEEK_CUR)
		suiCurrPos = suiCurrPos + (unsigned int) offset;
	else if (whence == SEEK_END)
		suiCurrPos = suiSize;
	//LOGI("suiCurrPos = %i , suiSize %i",suiCurrPos, suiSize);
	return 0;
}

static int close_func(void* datasource) {
	return 0;
}

static long tell_func(void* datasource) {
	return (long) suiCurrPos;
}
void OALOgg::Log() {
	LOGI("vi->channels = %i", vi->channels);
	LOGI("vi->rate = %i", vi->rate);
	LOGI("vi->version = %i", vi->version);
	LOGI("uiPCMSamples = %i", uiPCMSamples);
}
void OALOgg::getInfo(unsigned int uiOggSize, unsigned char* pvOggBuffer) {
	// Заменяем колбэки
	ov_callbacks callbacks;
	callbacks.read_func = &read_func;
	callbacks.seek_func = &seek_func;
	callbacks.close_func = &close_func;
	callbacks.tell_func = &tell_func;

	suiCurrPos = 0;
	suiSize = uiOggSize;
	int iRet = ov_open_callbacks(pvOggBuffer, &vf, NULL, 0, callbacks);

	// Заголовки
	vi = ov_info(&vf, -1);

	uiPCMSamples = (unsigned int) ov_pcm_total(&vf, -1);
	Log();
}
void OALOgg::getInfo() {
	// pvOggBuffer =  (char*)malloc(4096);
	//f->read(pvOggBuffer,4096,1);
	// Заменяем колбэки
	ov_callbacks callbacks;
	callbacks.read_func = (streaming) ? &read_func_streaming : &read_func;
	callbacks.seek_func = &seek_func;
	callbacks.close_func = &close_func;
	callbacks.tell_func = &tell_func;

	suiCurrPos = 0;
	suiSize = f->size();
	//LOGI("f->size() = %i",f->size());
	//int iRet = ov_open_callbacks(pvOggBuffer, &vf, NULL, 0, callbacks);
	int iRet = ov_open_callbacks(f, &vf, NULL, 0, callbacks);
	uiPCMSamples = (unsigned int) ov_pcm_total(&vf, -1);
	// Заголовки
	vi = ov_info(&vf, -1);
	Log();

	//free(pvOggBuffer);
	//delete(f);
}
unsigned char* OALOgg::readBlock(size_t size) {
//	if(buf != NULL)
//		free(buf);
//	buf = (unsigned char *) malloc(size);
//	iRead = ov_read(&vf, buf, size, &current_section);
//		return buf;
	unsigned char * data = (unsigned char *) malloc(size);
	iRead = ov_read(&vf, data, size, &current_section);
	return data;

//	if(buf != NULL)
//		free(buf);
//	buf = (unsigned char *) malloc(size);
//	iRead = ov_read(&vf, buf, size, &current_section);
//	return buf;

}
void * OALOgg::ConvertOggToPCM(unsigned int uiOggSize,
		unsigned char* pvOggBuffer) {
	if (suiSize == 0) {
		getInfo(uiOggSize, pvOggBuffer);
		current_section = 0;
		iRead = 0;
		uiCurrPos = 0;
	}

	void* pvPCMBuffer = malloc(uiPCMSamples * vi->channels * sizeof(short));

	// Декодим
	do {
		iRead = ov_read(&vf, (char*) pvPCMBuffer + uiCurrPos, 4096,&current_section);
		//iRead = ov_read(&vf, (char*) buf + uiCurrPos, 4096,&current_section);
		uiCurrPos += (unsigned int) iRead;
	} while (iRead != 0);

	free(pvOggBuffer);
	buf = (unsigned char *)pvPCMBuffer;
	return buf;
	//return pvPCMBuffer;
}
void OALOgg::createBufferFromOgg(unsigned char* data, int size, int index) {
	/*alGenBuffers(1,&buffer);
	 alBufferData(buffer,format,data,size,header.samplesPerSec);

	 if (source) {
	 alDeleteSources(1, &source);
	 delete data;
	 }

	 source = 0;
	 alGenSources(1, &source);
	 alSourcei(source, AL_BUFFER, buffer);*/

	//alGenBuffers(1,&buffers[index]);
	alBufferData(buffers[index], format, data, size, vi->rate);

}
void OALOgg::creatBuffer(int index) {
	//int count = Min(BUFFER_SIZE, this->riffCount -curPos);

	//int size = DEFAUULT_COUNT;//Min(BUFFER_SIZE, header.dataSize -curPos);
	//this->datas[index] = readRiffs(size);


	//unsigned char * data = readBlock(DEFAUULT_COUNT * vi->channels * sizeof(short));
	unsigned char * data = readBlock(BUFFER_SIZE);
	if (!data)
		return;


	createBufferFromOgg(data, BUFFER_SIZE, index);
	//GenSources(index);
}
void OALOgg:: loadWithStreaming(){
	getInfo();
	//LOGI("suiCurrPos = %i , suiSize %i", suiCurrPos, suiSize);
	if (vi->channels == 1)
		format = AL_FORMAT_MONO16;
	else
		format = AL_FORMAT_STEREO16;
	source = 0;


	alGenBuffers(BUFF_COUNT, buffers);

	alGenSources(1, &source);

	//buf = (unsigned char *)malloc(BUFFER_SIZE);

	/*
	 LOGI("source %i",source);
	 for(int i=0;i<BUFF_COUNT;++i)
	 LOGI("buf [%i] = %i",i,buffers[i]);*/

	if (alGetError() != AL_NO_ERROR) {
		LOGI("Error generating :(\n");
		return;
	}
	//LOGI("=/\n");

	for (int i = 0; i < BUFF_COUNT; ++i)
		creatBuffer(i);
	//LOGI("=/\n");
	if (alGetError() != AL_NO_ERROR) {
		LOGI("Error loading :(\n");
		return;
	}
	LOGI("suiCurrPos = %i , suiSize %i", suiCurrPos, suiSize);

	alSourceQueueBuffers(source, BUFF_COUNT, buffers);
	if (alGetError() != AL_NO_ERROR) {
		LOGI("Error alSourceQueueBuffers :(\n");
		return;
	}
}
void OALOgg:: loadWithoutStreaming(){
	buf = 0;
	buf = (unsigned char*) malloc(f->size());
	if (buf) {
		if (f->read(buf, f->size(), 1)) {
		} else {
			free(buf);
			f->close();
			return;
		}
	}

	//LOGI("f.size() = %i",f.size());
	//PreConvert(f.size(),buf);
	unsigned char * data = (unsigned char *) ConvertOggToPCM(f->size(), buf);

	f->close();
	//free(buf);
	if (vi->channels == 1)
		format = AL_FORMAT_MONO16;
	else
		format = AL_FORMAT_STEREO16;

	//alGenBuffers(1, &buffer);
	alGenBuffers(1, &buffers[0]);
	//LOGI("uiPCMSamples = %i", uiPCMSamples);
	//Log();
	//LOGI("sizeof(short) = %i",sizeof(short));
	//LOGI("Size = %u",uiPCMSamples * vi->channels * sizeof(short));

	//alBufferData(buffer, format, data, uiPCMSamples * vi->channels * sizeof(short), vi->rate);
	alBufferData(buffers[0], format, data, uiPCMSamples * vi->channels * sizeof(short), vi->rate);
	source = 0;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffers[0]);
	//alSourcei(source, AL_BUFFER, buffer);
}
void OALOgg::load(AAssetManager *mgr, const char* filename) {
	//this->filename = filename;
	//unsigned char* buf = 0;
	f = new AAssetFile(mgr, filename);
	if (f->null()) {
		LOGE("no file %s in readOgg", filename);
		return;
	}
	if(!streaming)

		loadWithoutStreaming();
	 else
		 loadWithStreaming();


	/*buf = 0;
	 buf = (char*)malloc(f.size());
	 if (buf){
	 if(f.read(buf,f.size(),1)){
	 }
	 else {
	 free(buf);
	 f.close();
	 return;
	 }
	 }

	 //LOGI("f.size() = %i",f.size());
	 //PreConvert(f.size(),buf);
	 char * data = (char *)ConvertOggToPCM(f.size(),buf);
	 f.close();

	 if (vi->channels == 1)
	 format = AL_FORMAT_MONO16;
	 else
	 format = AL_FORMAT_STEREO16;

	 alGenBuffers(1,&buffer);
	 //LOGI("uiPCMSamples = %i", uiPCMSamples);
	 //Log();
	 //LOGI("sizeof(short) = %i",sizeof(short));
	 //LOGI("Size = %u",uiPCMSamples * vi->channels * sizeof(short));

	 alBufferData(buffer,format,data,uiPCMSamples * vi->channels * sizeof(short),vi->rate);

	 source = 0;
	 alGenSources(1, &source);
	 alSourcei(source, AL_BUFFER, buffer);*/
}

void OALOgg::play() {

	if (!streaming) {

		alSourcePlay(source);

		do {
		} while (isPlaying());
	} else {

		alSourcePlay(source);

		while (true) {
			//while(curPos<ov_pcm_total(mVF, -1) * 4){
			ALint val;
			ALuint buffer;

			alGetSourcei(source, AL_BUFFERS_PROCESSED, &val);

			if (val <= 0)
				continue;

			while (val--) {
				unsigned char * data = this->readBlock(BUFFER_SIZE);// readRiffs(size);


				alSourceUnqueueBuffers(source, 1, &buffer);

				alBufferData(buffer, format, data, BUFFER_SIZE, vi->rate);

				alSourceQueueBuffers(source, 1, &buffer);

				if (alGetError() != AL_NO_ERROR) {
					LOGI("Error buffering :(\n");

				}
			}
		}
		//}
	}
}
