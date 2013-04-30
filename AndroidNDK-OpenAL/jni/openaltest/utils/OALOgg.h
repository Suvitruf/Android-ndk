// OALOgg.h
// Обёртка для .ogg файла


#include "OALSound.h"

#include <os.h>
#include <config_types.h>
#include "ivorbisfile.h"

class OALOgg : public OALSound{
public:

	//ALenum format;
	OALOgg();
	~OALOgg();
	virtual void load(AAssetManager *mgr, const char* filename);
	virtual void play();
private:
	 vorbis_info* vi;
	 unsigned int uiPCMSamples;
	void * ConvertOggToPCM(unsigned int uiOggSize,  char* pvOggBuffer);
	void Log();
	void getInfo(unsigned int uiOggSize, char* pvOggBuffer);
	OggVorbis_File vf;
	unsigned int uiCurrPos;
	int current_section ;
	long iRead;
};
