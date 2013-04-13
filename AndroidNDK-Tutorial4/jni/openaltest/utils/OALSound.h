#include "OALContext.h"
#include <al.h>
#include <alc.h>
#include "AAssetFile.h"
#include "trace.h"
#include <os.h>
#include <config_types.h>
#include "ivorbisfile.h"
class OALSound
{


public:
	//enum Format{mp3,wav,ogg};
	OALSound();
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

	void play();
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

    virtual void load(AAssetManager *mgr, const char* filename)= 0;
protected:
    //bool streaming;
    ALuint source;
    const char * filename;

    ALuint   buffer;
    ALenum format;
    char * data;
private:

    //int sampleRate;
    //bool bindToData();
    //ALsizei dataLength;
    //Format format;
};




typedef struct {
  char  riff[4];//'RIFF'
  unsigned int riffSize;
  char  wave[4];//'WAVE'
  char  fmt[4];//'fmt '
  unsigned int fmtSize;
  unsigned short format;
  unsigned short channels;
  unsigned int samplesPerSec;
  unsigned int bytesPerSec;
  unsigned short blockAlign;
  unsigned short bitsPerSample;
  char  data[4];//'data'
  unsigned int dataSize;
}BasicWAVEHeader;

class OALWav : public OALSound{
public:
	//AAssetFile f;
	OALWav();
	~OALWav();
	virtual void load(AAssetManager *mgr, const char* filename);
	//virtual void play();
private:
	char* readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header);
	void createBufferFromWave(char* data);
	//void createBufferFromWave(char* data, int size);
	void getFormat();
	//char* readFrame();
	BasicWAVEHeader header;
	//AAssetManager *mgr;
	//unsigned int curPos;
	//unsigned int frameSize;
};

class OALOgg : public OALSound{
public:

	//ALenum format;
	OALOgg();
	~OALOgg();
	virtual void load(AAssetManager *mgr, const char* filename);
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
