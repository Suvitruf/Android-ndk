// OALWav.h
#ifndef _OALWav_
#define _OALWav_

#include "OALSound.h"


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

class OALWav : public OALSound{
public:

	OALWav();
	OALWav(bool streaming);
	OALWav(AAssetManager *mgr, char * fileName, bool streaming);
	~OALWav();
	void load(AAssetManager *mgr, const char* filename);
	void play();
	//void setVolume(float volume, int iBuffer);
private:
	void loadWithStreaming();
	void loadWithoutStreaming();
	/**
	 * Reading file entirely
	 */
	unsigned char* readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header);
	/**
	 * Reading some blicks
	 */
	unsigned char* readRiffs(int count);

	void createBufferFromWave(unsigned char* data);

	void createBufferFromWave(unsigned char* data, int size, int index);
	void getFormat();
	void GenSources();
	//void GenSources(int index);
	void LogHeaders();

	void creatBuffer(int index);

	//unsigned int riffCount;
	//float getOffset();
	BasicWAVEHeader header;
	//AAssetManager *mgr;
	unsigned int curPos;
	//unsigned int riffSize;
	//short currentBuff;

	//int pid;
};

#endif
