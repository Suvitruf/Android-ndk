// OALOgg.h
#ifndef _OALOgg_
#define _OALOgg_


#include "OALSound.h"

#include <os.h>
#include <config_types.h>
#include "ivorbisfile.h"

//#define DEFAUULT_COUNT 4096
class OALOgg : public OALSound{
public:

	//ALenum format;
	OALOgg();
	OALOgg(bool streaming);
	OALOgg(AAssetManager *mgr, char * fileName, bool streaming);
	~OALOgg();
	virtual void load(AAssetManager *mgr, const char* filename);
	virtual void play();
private:
	vorbis_info* vi;
	unsigned int uiPCMSamples;

	void loadWithStreaming();
	void loadWithoutStreaming();
	void * ConvertOggToPCM(unsigned int uiOggSize, unsigned  char* pvOggBuffer);
	void Log();
	void getInfo(unsigned int uiOggSize,unsigned  char* pvOggBuffer);
	unsigned char* readBlock(size_t count);
	void getInfo();

	void creatBuffer(int index);
	void createBufferFromOgg(unsigned char* data, int size, int index);
	OggVorbis_File vf;
	unsigned int uiCurrPos;
	int current_section ;
	long iRead;

	//AAssetFile * f;
};

#endif
