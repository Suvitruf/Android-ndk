// OALWav.h
// Обёртка для .wav файла

#include "OALSound.h"


/**
 * Структура хэдера WAV
 */
typedef struct {
  char  riff[4];				// 'RIFF'
  unsigned int riffSize;		// Размер чанка ‘RIFF’
  char  wave[4];				// 'WAVE'
  char  fmt[4];					// 'fmt '
  unsigned int fmtSize;			// размер fmt-чанка
  unsigned short format; 	    // Формат звуковых данных
  unsigned short channels;      // Количество каналов
  unsigned int samplesPerSec;	// Частота дискретизации аудиосигнала
  unsigned int bytesPerSec;     // Количество байт передаваемых в секунду
  unsigned short blockAlign;    // Выравнивание данных в чанке данных
  unsigned short bitsPerSample; // Количество бит на одну выборку сигнала
  char  data[4];				// 'data'
  unsigned int dataSize;		// размер блока с самими данынми
}BasicWAVEHeader;

class OALWav : public OALSound{
public:
	AAssetFile f;
	OALWav();
	OALWav(bool streaming);
	~OALWav();
	void load(AAssetManager *mgr, const char* filename);
	void play();
	//void setVolume(float volume, int iBuffer);
private:
	/**
	 * Прочитать файл целиком.
	 */
	unsigned char* readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header);
	/**
	 * Прочитать определённое количество чанков
	 */
	unsigned char* readRiffs(int count);
	/**
	 * Создание OpenAL буфера
	 */
	void createBufferFromWave(unsigned char* data);
	/**
	 * Создание OpenAL буфера по определённому индексу в списке буферов
	 */
	void createBufferFromWave(unsigned char* data, int size, int index);
	void getFormat();
	void GenSources();
	//void GenSources(int index);
	void LogHeaders();
	/**
	 * Создание буфера по определённому индексу
	 */
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
