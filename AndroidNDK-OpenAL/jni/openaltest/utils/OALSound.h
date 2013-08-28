// OALSound.h
#ifndef _OALSound_
#define _OALSound_


#include <al.h>
#include <alc.h>

#include "trace.h"
#include "AAssetFile.h"

#define BUFFER_SIZE 4096
#define BUFF_COUNT 4
class OALSound
{


public:
	OALSound();
	OALSound(bool streaming);
	//OALSound(AAssetManager *mgr, const char * fileName, bool streaming);
	virtual ~OALSound();


    //void loadFromBuffer(SunnyALBuffer * buf);
	void setVolume(float volume);
	float getVolume();
	//void setPitch(float  volume);
	//float getPitch();
	void setLooping(bool looping);
	//bool isLooping();
	//void setReferenceDistance(float d);
	//float getReferenceDistance();

	//Format getFormat();


	virtual void play() = 0;
	void pause();
	void rewind();
	void stop();
	int state();

	bool isActive();
	bool isInitializing();
	bool isPlaying();
	bool isPaused();
	bool isStopped();
    void setOffset(float offset);
    virtual float getOffset();
    virtual void load(AAssetManager *mgr, const char* filename)= 0;
protected:

    bool streaming;
    ALuint source;
    //ALuint sources[BUFF_COUNT];
    //const char * filename;

    //ALuint   buffer;
    ALuint   buffers[BUFF_COUNT];
    ALenum format;
    //unsigned  char * data;
    unsigned char * buf;
    //unsigned char * bufs[BUFF_COUNT];
    AAssetFile * f;
    //char * datas[BUFF_COUNT];
private:

    //int sampleRate;
    //bool bindToData();
    //ALsizei dataLength;
    //Format format;
};




unsigned int Min( unsigned int agr1,  unsigned int agr2);


#endif

