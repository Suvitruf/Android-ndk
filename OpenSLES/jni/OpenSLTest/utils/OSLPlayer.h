#ifndef _OSLPlayer_
#define _OSLPlayer_
#include "trace.h"
#include "OSLContext.h"
#include "assert.h"

class OSLContext;
class OSLSound;

class OSLPlayer{
public:
	OSLPlayer(OSLContext * context);
	virtual ~OSLPlayer();

	float getVolume() ;
	void setVolume(float volume) ;
//	virtual void resume() = 0;
	virtual void pause() = 0;
	virtual void play() = 0;
	virtual void stop() = 0;
	virtual SLuint32 state();
	virtual void Log()=0;
	bool isPlaying();
	bool isPaused();
	bool isStopped();
	virtual void setSound(OSLSound * sound) = 0;
	OSLSound * sound;
//	void setBuffer(char * buf, long dataSize);
protected:
	virtual void clear();
//	void clearLastSoundIfNeeded(OSLSound * sound);
//	char * fileName;

	OSLContext * context;
	SLmillibel gain_to_attenuation( float gain);

	SLDataSource audioSrc;
	SLDataLocator_OutputMix locatorOutMix;
	SLDataSink audioSnk;
	SLVolumeItf fdPlayerVolume;
	SLObjectItf playerObj;
	SLPlayItf player;
};

#endif
