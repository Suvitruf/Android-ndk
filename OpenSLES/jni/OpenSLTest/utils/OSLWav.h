// OSLWav.h
#ifndef _OSLWav_
#define _OSLWav_


#include "OSLSound.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
/**
 * The canonical WAVE format starts with the RIFF header
 */
typedef struct {
  char  riff[4];				// Contains the letters "RIFF" in ASCII form
  	  	  	  	  	  	  	    // (0x52494646 big-endian form).
  unsigned int riffSize;		// 36 + SubChunk2Size, or more precisely:
								// 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
								// This is the size of the rest of the chunk
								// following this number.  This is the size of the
								// entire file in bytes minus 8 bytes for the
								// two fields not included in this count:
								// ChunkID and ChunkSize.

  char  wave[4];				// Contains the letters "WAVE"
  	  	  	  	  	  	  	  	//(0x57415645 big-endian form).

  char  fmt[4];					// Contains the letters "fmt"
  	  	  	  	  	  	  	  	// (0x666d7420 big-endian form).

  unsigned int fmtSize;			// 16 for PCM.  This is the size of the
  	  	  	  	  	  	  	  	// rest of the Subchunk which follows this number.

  unsigned short format; 	    // PCM = 1 (i.e. Linear quantization)Values other than 1 indicate some form of compression.
  unsigned short channels;      // Mono = 1, Stereo = 2, etc.
  unsigned int samplesPerSec;	// Sampling rate (8000, 44100, etc.)
  unsigned int bytesPerSec;     // samplesPerSec * channels * bitsPerSample/8

  unsigned short blockAlign;    // NumChannels * BitsPerSample/8
  	  	  	  	  	  	  	  	// The number of bytes for one sample including all channels.

  unsigned short bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
  char  data[4];				// 'data'
  unsigned int dataSize;		// The actual sound data.
}BasicWAVEHeader;

class OSLWav : public OSLSound{
public:

	//OSLWav();
//	OSLWav(OSLContext context);
//	float getVolume();
//	void setVolume(float volume);
	OSLWav( OSLContext * context,PlayerType playerType);
	OSLWav( OSLContext * context,PlayerType playerType, char * path);
	~OSLWav();
	void load( char* filename);
//	void pause();
//	void stop();
//	void play();
//	bool isPlaying();

//	void initBuf();
	long getSize();
	char * getBuffer();
	BasicWAVEHeader header;
private:
	AAsset* openFile(char * path);
	long dataSize;

	char* readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header);

	void getFormat();
	void GenSources();
	void LogHeaders();

	char*  buf ;

//	void createBufferQueuePlayer();


//	SLInterfaceID pIDs[1];
//    SLboolean pIDsRequired[1];


};

#endif
