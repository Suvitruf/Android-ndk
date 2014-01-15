#ifndef _OSLBufferPlayer_
#define _OSLBufferPlayer_
//#include "trace.h"
#include "OSLContext.h"
#include "assert.h"

class OSLContext;
class OSLSound;


class OSLBufferPlayer : public OSLPlayer {
public:
	OSLBufferPlayer(OSLContext * context);
	~OSLBufferPlayer();

//	float getVolume();
//	void setVolume(float volume);
	void pause();
	void play();
	void stop();
//	SLuint32 state();
//	bool isPlaying();
//	bool isPaused();
//	bool isStopped();
	void setSound(OSLSound * sound);
	void Log();
	SLuint32 state();
//	OSLSound * lastSound;
//	void replaySound();
//	void setBuffer(char * buf, long dataSize);
private:

//	void PlayEventCallback( SLPlayItf caller,  void *pContext, SLuint32 event);
	void init();
//	OSLContext * context;
	SLBufferQueueItf bufferQueue;

};

#endif
