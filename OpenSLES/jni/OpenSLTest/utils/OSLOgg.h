#ifndef _OSLOgg_
#define _OSLOgg_


#include "OSLSound.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <os.h>
#include <config_types.h>
#include "ivorbisfile.h"


class OSLOgg : public OSLSound{
public:

	//OSLWav();
//	OSLWav(OSLContext context);
//	float getVolume();
//	void setVolume(float volume);
	OSLOgg( OSLContext * context, PlayerType playerType);
	OSLOgg( OSLContext * context,PlayerType playerType, char * path);
	~OSLOgg();
	void load( char* filename);
//	void pause();
//	void stop();
//	void play();
//	bool isPlaying();

//	void initBuf();
	long getSize();
	char * getBuffer();

private:

	long size;
	unsigned int uiCurrPos;
	int current_section ;
	unsigned int uiPCMSamples;
	vorbis_info* vi;
    char * buf;
    OggVorbis_File vf;


    AAsset* openFile(char * path);
    void * ConvertOggToPCM(unsigned int uiOggSize,	char* pvOggBuffer);

    void getInfo(unsigned int uiOggSize, char* pvOggBuffer);
//    unsigned char* readBlock(size_t count);
	void Log() ;
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
