#include "OALSound.h"



OALSound::OALSound()
{
	//streaming = true;
}

OALSound::~OALSound()
{
	if (source) alDeleteSources(1, &source);
	delete data;
	//delete buffer;
	//checkError();
}
/*
void OALSound::loadFromFile(const char * fileName)
{
	alGenSources(1, &source);
	checkError();

	buffer = new SunnyALBuffer;
	if(buffer->loadFromFile(fileName))

		alSourcei(source, AL_BUFFER, buffer->alcBuffer);


}*/
/*
void OALSound::loadFromBuffer(SunnyALBuffer * buf)
{
    alGenSources(1, &source);
	checkError();

    buffer = buf;
    alSourcei(source, AL_BUFFER, buffer->alcBuffer);
}*/

void OALSound::setVolume(float volume)
{
	alSourcef(source, AL_GAIN, volume);
	//checkError();
}

void OALSound::setOffset(float offset)
{
    alSourcef(source, AL_SEC_OFFSET, offset);
    //checkError();
}

float OALSound::getVolume()
{
	float volume;
	alGetSourcef(source, AL_GAIN, &volume);
	//checkError();
	return volume;
}
/*
OALSound::Format OALSound::getFormat(){
	return format;
}*/
/*
void OALSound::setPitch(float v)
{
	alSourcef(source, AL_PITCH, v);
	checkError();
}

float SunnyALSource::getPitch()
{
	float v;
	alGetSourcef(source, AL_PITCH, &v);
	checkError();
	return v;
}*/

void OALSound::setLooping(bool aBool)
{
	alSourcei(source, AL_LOOPING, aBool ? AL_TRUE : AL_FALSE);
	//checkError();
}
/*
bool OALSound::isLooping()
{
	int v;
	alGetSourcei(source, AL_LOOPING, &v);
	//checkError();
	return v;
}*/
/*
void OALSound::setReferenceDistance(float d)
{
	alSourcef(source, AL_REFERENCE_DISTANCE, d);
	checkError();
}

float OALSound::getReferenceDistance()
{
	float v;
	alGetSourcef(source, AL_REFERENCE_DISTANCE, &v);
	checkError();
	return v;
}*/

void OALSound::play()
{

/*
	ALuint source = 0;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);*/

	//if(!streaming){
	alSourcePlay(source);

	int sourceState = AL_PLAYING;
	do {
		 alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
	} while(sourceState == AL_PLAYING);
	//}
	/*else{
		alSourcePlay(source);

		int sourceState = AL_PLAYING;
		do{
			createBufferFromWave(data,header.channels*header.samplesPerSec);
		}while(true);
	}*/


	//if (checkError()) return false;
	//return true;
}

void OALSound::pause()
{
	alSourcePause(source);
	//checkError();
}

void OALSound::rewind()
{
	alSourceRewind(source);
	//checkError();
}

void OALSound::stop()
{
	alSourceStop(source);
	//checkError();
}

int OALSound::state()
{
	int state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	//checkError();
	return state;
}

bool OALSound::isActive()
{
	int newState = state();
	return !(newState == AL_INITIAL || newState == AL_STOPPED);
}

bool OALSound::isInitializing()
{
	return state() == AL_INITIAL;
}

bool OALSound::isPlaying()
{
	return state() == AL_PLAYING;
}

bool OALSound::isPaused()
{
	return state() == AL_PAUSED;
}

bool OALSound::isStopped()
{
	return state() == AL_STOPPED;
}



OALWav::OALWav():OALSound()
{
	format = 0;
}

OALWav::~OALWav()
{

}

/*void OALWav::play()
{



	if(!streaming){

		alSourcePlay(source);

		int sourceState = AL_PLAYING;
		 do {
			 alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
		 } while(sourceState == AL_PLAYING);
	}
	else{
		if(curPos>=header.dataSize) return;


		int sourceState = AL_PLAYING;
		do{
			alSourcePlay(source);

			char * r = readFrame();
			if(!r)
				return;
			createBufferFromWave(data,this->frameSize);
			alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
		}while(true);
	}


	//if (checkError()) return false;
	//return true;
}*/
/*
char* OALWav::readFrame(){
	char* buffer = 0;
	if(curPos>=header.dataSize) {

		f.close();
		return 0;
	}
	//LOGI("curPos = %i",curPos);
	if (!(
				// Заголовки должны быть валидны.
				// Проблема в том, что не всегда так.
				// Многие конвертеры недобросовестные пихают в эти заголовки свои логотипы =/
				memcmp("RIFF",header.riff,4) ||
				memcmp("WAVE",header.wave,4) ||
				memcmp("fmt ",header.fmt,4)  ||
				memcmp("data",header.data,4)
			)){
				//LOGI("data riff = %s", header.riff);
				//LOGI("header.channels = %i", header.channels);
				buffer = (char*)malloc(this->frameSize);

				if (buffer){
					//LOGI("header.samplesPerSec = %i",header.bitsPerSample);
					int r = f.read(buffer,this->frameSize,1);
					//LOGI("header.samplesPerSec = %i",header.bitsPerSample);
					if(r){
						//LOGI("r = %i",r);
						curPos+=r;
						return buffer;
					}
					free(buffer);

				}
			}
	f.close();
	return 0;
}*/
char* OALWav::readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header){
	char* buffer = 0;

	AAssetFile f = AAssetFile(mgr, filename);

	if (f.null()) {
		LOGE("no file %s in readWAV",filename);
		return 0;
	}


	int res = f.read(header,sizeof(BasicWAVEHeader),1);
	//LOGI("read %i bytes from %s", res,filename );
	if(res){
		//LOGI("AAsset_read %s,",filename);
		if (!(
			// Заголовки должны быть валидны.
			// Проблема в том, что не всегда так.
			// Многие конвертеры недобросовестные пихают в эти заголовки свои логотипы =/
			memcmp("RIFF",header->riff,4) ||
			memcmp("WAVE",header->wave,4) ||
			memcmp("fmt ",header->fmt,4)  ||
			memcmp("data",header->data,4)
		)){
			//LOGI("data riff = %s", header->riff);
			//LOGI("data size = %u", header->dataSize);
			buffer = (char*)malloc(header->dataSize);
			if (buffer){
				if(f.read(buffer,header->dataSize,1)){
					f.close();
					return buffer;
				}
				free(buffer);
			}
		}
	}
	f.close();
	return 0;
}

void OALWav::getFormat(){
	switch (header.bitsPerSample){
		case 8:
			format = (header.channels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
			break;
		case 16:
			format = (header.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
			break;
		default:
			return ;
		}
}
/*
void  OALWav::createBufferFromWave(char* data, int size){
	alGenBuffers(1,&buffer);
	alBufferData(buffer,format,data,size,header.samplesPerSec);

	if (source) {
		alDeleteSources(1, &source);
		delete data;
	}

	source = 0;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
}*/
void OALWav:: createBufferFromWave(char* data){
	alGenBuffers(1,&buffer);
	alBufferData(buffer,format,data,header.dataSize,header.samplesPerSec);
}

void OALWav::load(AAssetManager *mgr, const char* filename){
	//this->mgr = mgr;
	this->filename = filename;
	this->data = 0;
	//if(!streaming){
	this->data = this->readWAVFull(mgr, &header);
	getFormat();
	createBufferFromWave(data);
	source = 0;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	//}
	/*else{
		this->curPos = 0;
		f = AAssetFile(mgr, filename);

		if (f.null()) {
			LOGE("no file %s in readWAV",filename);
			return;
		}
		LOGI("1");
		int res = f.read(&header,sizeof(BasicWAVEHeader),1);
		LOGI("2");
		getFormat();
		LOGI("3");
		this->frameSize = header.channels*header.samplesPerSec;
		char * r = readFrame();

		if(!r)
			return;

		createBufferFromWave(data,this->frameSize);

	}*/



}


OALOgg::OALOgg():OALSound()
{

}

OALOgg::~OALOgg()
{
	ov_clear(&vf);
}


unsigned int suiCurrPos = 0;
unsigned int suiSize = 0;
unsigned int Min( unsigned int agr1,  unsigned int agr2){
	return (agr1 <agr2) ?agr1 : agr2;
}
static size_t  read_func(void* ptr, size_t size, size_t nmemb, void* datasource)
{
    unsigned int uiBytes = Min(suiSize - suiCurrPos, (unsigned int)nmemb * (unsigned int)size);
    memcpy(ptr, (unsigned char*)datasource + suiCurrPos, uiBytes);
    suiCurrPos += uiBytes;

    return uiBytes;
}

static int seek_func(void* datasource, ogg_int64_t offset, int whence)
{
    if (whence == SEEK_SET)
        suiCurrPos = (unsigned int)offset;
    else if (whence == SEEK_CUR)
        suiCurrPos = suiCurrPos + (unsigned int)offset;
    else if (whence == SEEK_END)
        suiCurrPos = suiSize;

    return 0;
}

static int close_func(void* datasource)
{
    return 0;
}

static long tell_func(void* datasource)
{
    return (long)suiCurrPos;
}
void OALOgg::Log(){
	LOGI("vi->channels = %i",vi->channels);
	LOGI("vi->rate = %i",vi->rate);
	LOGI("vi->version = %i",vi->version);
}
void OALOgg::getInfo(unsigned int uiOggSize, char* pvOggBuffer){
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

	    uiPCMSamples = (unsigned int)ov_pcm_total(&vf, -1);
}
void * OALOgg::ConvertOggToPCM(unsigned int uiOggSize, char* pvOggBuffer)
{
	if(suiSize == 0){
		getInfo( uiOggSize, pvOggBuffer);
		current_section = 0;
		iRead = 0;
		uiCurrPos = 0;
	}



    void* pvPCMBuffer = malloc(uiPCMSamples * vi->channels * sizeof(short));

    // Декодим
    do
    {
        iRead = ov_read(&vf, (char*)pvPCMBuffer + uiCurrPos, 4096, &current_section);
        uiCurrPos += (unsigned int)iRead;
    }
    while (iRead != 0);

    return pvPCMBuffer;
}

void OALOgg::load(AAssetManager *mgr, const char* filename){
	this->filename = filename;
	char* buf = 0;
	AAssetFile f = AAssetFile(mgr, filename);
	if (f.null()) {
		LOGE("no file %s in readOgg",filename);
		return ;
	}

	buf = 0;
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
	alSourcei(source, AL_BUFFER, buffer);
}
