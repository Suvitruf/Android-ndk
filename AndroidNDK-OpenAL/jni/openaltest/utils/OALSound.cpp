#include "OALSound.h"
#include "unistd.h"

unsigned int Min( unsigned int agr1,  unsigned int agr2){
	return (agr1 <agr2) ?agr1 : agr2;
}

OALSound::OALSound(){
	this->streaming = false;
}
/*OALSound::OALSound(AAssetManager *mgr, const char * fileName, bool streaming){
	this->streaming = false;

}*/
OALSound::OALSound(bool streaming){
	this->streaming = streaming;
}

OALSound::~OALSound()
{
	if (source) alDeleteSources(1, &source);
	alDeleteBuffers(BUFF_COUNT, buffers);
	if(buf != NULL) free(buf);
	/*for(int i=0;i<BUFF_COUNT;++i)
		if(bufs[i] != NULL) free(bufs[i]);*/

	if(f != NULL) delete f;
	//delete buffer;
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
float OALSound::getOffset()
{
	float offset;
	alGetSourcef(source, AL_SAMPLE_OFFSET, &offset );
	return offset;

    //alSourcef(source, AL_SEC_OFFSET, offset);
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

/*void OALSound::play()
{


	//if(!streaming){
	alSourcePlay(source);

	int sourceState = AL_PLAYING;
	do {
		 alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
	} while(sourceState == AL_PLAYING);

}*/

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
	LOGI("stoped");
	alSourceStop(source);


	//checkError();
}

int OALSound::state()
{
	int state;
	//if(!streaming)
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	//else
	//	alGetSourcei(source, AL_BUFFERS_PROCESSED,&state);
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





