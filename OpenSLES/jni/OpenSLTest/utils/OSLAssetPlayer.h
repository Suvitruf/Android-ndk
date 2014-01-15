#ifndef _OSLAssetPlayer_
#define _OSLAssetPlayer_

#include "OSLContext.h"
#include "assert.h"


class OSLContext;
class OSLSound;
//class OSLPlayer;

class OSLAssetPlayer  : public OSLPlayer{
public:
	OSLAssetPlayer(OSLContext * context);
	~OSLAssetPlayer();
	void Log(){}
	void pause();
	void play();
	void stop();
	void setSound(OSLSound * sound);
private:
	void init(char * filename);
	void clear();


//	SLObjectItf outputMixObject;
//	SLDataLocator_OutputMix locatorOutputMix;
//	SLDataFormat_PCM formatPCM;
//	SLDataSource audioSrc;
//	SLDataLocator_OutputMix locatorOutMix;
//	SLDataSink audioSnk;
	SLSeekItf fdPlayerSeek;
	SLMuteSoloItf fdPlayerMuteSolo;
//	SLVolumeItf fdPlayerVolume;

//	SLObjectItf playerObj;
//	SLPlayItf player;
};

#endif
