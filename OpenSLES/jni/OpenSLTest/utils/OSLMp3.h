#ifndef _OSLMp3_
#define _OSLMp3_


#include "OSLSound.h"


class OSLMp3 : public OSLSound{
public:

	//OSLWav();
//	OSLWav(OSLContext context);
//	float getVolume();
//	void setVolume(float volume);
	OSLMp3( OSLContext * context);
	OSLMp3( OSLContext * context, char * path);
	~OSLMp3();
	void load( char* filename);
//	void pause();
//	void stop();
//	void play();
//	bool isPlaying();

//	void initBuf();
//	long getSize();
//	char * getBuffer();

private:
//	AAsset* openFile(char * path);
//	long dataSize;

//	char* readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header);

//	void getFormat();
//	void GenSources();
//	void LogHeaders();

//	char*  buf ;

//	void createBufferQueuePlayer();


//	SLInterfaceID pIDs[1];
//    SLboolean pIDsRequired[1];


};

#endif
