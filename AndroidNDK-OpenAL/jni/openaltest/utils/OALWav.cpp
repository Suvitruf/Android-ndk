#include "OALWav.h"

OALWav::OALWav():OALSound()
{
	format = 0;
}
OALWav::OALWav(bool streaming):OALSound(streaming){

}

OALWav::OALWav(AAssetManager *mgr, char * fileName, bool streaming):OALSound(streaming){
	load(mgr,fileName);
}

OALWav::~OALWav()
{
	f->close();
}
//int i=0;





/*float OALWav::getOffset()
{
	float offset;
	//if(!streaming)
		alGetSourcef(source, AL_SAMPLE_OFFSET, &offset );
	//else
	//	alGetSourcef(sources[this->currentBuff], AL_SAMPLE_OFFSET, &offset );

	return offset;
    //alSourcef(source, AL_SEC_OFFSET, offset);
    //checkError();
}*/

void OALWav::play()
{



	if(!streaming){


		alSourcePlay(source);
		//int sourceState = AL_PLAYING;
		 do {
			 //alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
		 } while(isPlaying());//while(sourceState == AL_PLAYING);
	}

	else{
		//pid = fork();


		alSourcePlay(source);
		/*int sourceState = AL_PLAYING;
		do {
			alGetSourcei(source, AL_SOURCE_STATE, &sourceState);

			LOGI("sourceState %i",sourceState);
		} while(sourceState == AL_PLAYING);*/

		//LOGI("-11");
		//return;

		while(curPos<header.dataSize){
			ALint val;
			ALuint buffer;

			alGetSourcei(source, AL_BUFFERS_PROCESSED, &val);
			if(val <= 0)
				continue;

			 while(val--){

				 int size = Min(BUFFER_SIZE, header.dataSize -curPos);

				 unsigned  char * data = readRiffs(size);


				 alSourceUnqueueBuffers(source, 1, &buffer);

				 alBufferData(buffer, format, data, size, header.samplesPerSec);

			     alSourceQueueBuffers(source, 1, &buffer);

			     if(alGetError() != AL_NO_ERROR) {
			    	  LOGI("Error buffering :(\n");

			     }
			  }
			//alSourcePlay(sources[currentBuff]);


			/*int sourceState = AL_PLAYING;
			do {
				//alGetSourcei(sources[currentBuff], AL_SOURCE_STATE, &sourceState);
				float _offset = this->getOffset();
				//LOGI(" - %f samples\n", _offset);

			} while(sourceState == AL_PLAYING);*/
			//this->setVolume(0);
			//this->stop();
			//return;
			//
			//if (sources[currentBuff]) alDeleteSources(1, &sources[currentBuff]);
			//alDeleteBuffers(1, &buffers[currentBuff]);
			//delete data;
			//data = 0;
			//
			//return;
			/*currentBuff = currentBuff+1<BUFF_COUNT ? currentBuff+1 : 0;
			int count = Min(BUFFER_SIZE, this->riffCount -curPos);
			this->datas[currentBuff] = readRiffs(count );

			if(!this->datas[currentBuff])
			return;

			createBufferFromWave(datas[currentBuff],this->riffSize*(count ), currentBuff);
			GenSources();*/
			//sleep(5);




		}

		/*if(curPos>=header.dataSize) return;


		int sourceState = AL_PLAYING;
		do{
			alSourcePlay(source);

			char * r = readFrame();
			if(!r)
				return;
			createBufferFromWave(data,this->frameSize);
			alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
		}while(true);*/
	}


	//if (checkError()) return false;
	//return true;
}

unsigned char* OALWav::readRiffs(int size){
	//char* buffer = 0;
	if(/*curPos>=header.dataSize*/curPos>=header.dataSize) {

		f->close();
		return 0;
	}
	//LOGI("curPos = %i",curPos);
	//if (!(
	//			memcmp("RIFF",header.riff,4) ||
	//			memcmp("WAVE",header.wave,4) ||
	//			memcmp("fmt ",header.fmt,4)  ||
	//			memcmp("data",header.data,4)
	//		))
	{
				//LOGI("data riff = %s", header.riff);
				//LOGI("header.channels = %i", header.channels);
				//buf = (char*)malloc(size);
				//buffer = (char*)calloc(this->riffSize*count,1);
				//LOGI("this->riffSize*count %i",this->riffSize*count);
				if (buf){
					//LOGI("header.samplesPerSec = %i",header.bitsPerSample);
					int r = f->read(buf,size,1);
					//LOGI("header.samplesPerSec = %i",header.bitsPerSample);
					if(r){
						curPos +=r;
						return buf;
					}
					free(buf);

				}
			}
	f->close();
	return 0;
}
unsigned char* OALWav::readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header){
	//unsigned char* buffer = 0;

	//AAssetFile
	//f = AAssetFile(mgr, filename);

	if (f->null()) {
		LOGE("no file");
		return 0;
	}


	int res = f->read(header,sizeof(BasicWAVEHeader),1);
	//LOGI("read %i bytes from %s", res,filename );
	if(res){
		//LOGI("AAsset_read %s,",filename);
		//if (!(
		//	memcmp("RIFF",header->riff,4) ||
		//	memcmp("WAVE",header->wave,4) ||
		//	memcmp("fmt ",header->fmt,4)  ||
		//	memcmp("data",header->data,4)
		//))
		{
			//LOGI("data riff = %s", header->riff);
			//LOGI("data size = %u", header->dataSize);
			buf = (unsigned char*)malloc(header->dataSize);
			if (buf){
				if(f->read(buf,header->dataSize,1)){
					f->close();
					return buf;
				}
				free(buf);
			}
		}
	}
	f->close();
	return 0;
}

void OALWav::getFormat(){
	switch (header.bitsPerSample){
		case 8:
			format = (header.channels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
			break;
		case 16:
			format = (header.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
			break;
		default:
			return ;
		}
}


void  OALWav::createBufferFromWave(unsigned char* data, int size, int index){
	/*alGenBuffers(1,&buffer);
	alBufferData(buffer,format,data,size,header.samplesPerSec);

	if (source) {
		alDeleteSources(1, &source);
		delete data;
	}

	source = 0;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);*/

	//alGenBuffers(1,&buffers[index]);
	alBufferData(buffers[index],format,data,size,header.samplesPerSec);

}
void OALWav:: createBufferFromWave(unsigned char* data){
	//if(!streaming){
	//alGenBuffers(1,&buffer);
	//alBufferData(buffer,format,data,header.dataSize,header.samplesPerSec);
	alGenBuffers(1,&buffers[0]);
	alBufferData(buffers[0],format,data,header.dataSize,header.samplesPerSec);
	//}
	/*else{
		alGenBuffers(1,&buffers[currentBuff]);
		alBufferData(buffers[currentBuff],format,datas[currentBuff],header.dataSize,header.samplesPerSec);
	}*/
}
/*
void OALWav::GenSources(int index){
	sources[index] = 0;
	alGenSources(1, &sources[index]);
	alSourcei(sources[index], AL_BUFFER, buffers[index]);
}*/
void OALWav::GenSources(){
	if(!streaming){
		source = 0;
		alGenSources(1, &source);
		//alSourcei(source, AL_BUFFER, buffer);
		alSourcei(source, AL_BUFFER, buffers[0]);
	}
	/*else{
		sources[currentBuff] = 0;
		alGenSources(1, &sources[currentBuff]);
		alSourcei(sources[currentBuff], AL_BUFFER, buffers[currentBuff]);
	}*/
}

void OALWav::LogHeaders(){
	LOGI("dataSize = %i ",header.dataSize);
	LOGI("bitsPerSample = %i ",header.bitsPerSample);
	LOGI("bytesPerSec = %i ",header.bytesPerSec);
	LOGI("samplesPerSec = %i ",header.samplesPerSec);
	LOGI("fmtSize = %i ",header.fmtSize);
	LOGI("riffSize = %i ",	header.riffSize);
	LOGI("channels = %i ",	header.channels);
}

void OALWav::loadWithStreaming(){
	this->curPos = 0;
	//f = AAssetFile(mgr, filename);

	if (f->null()) {
		LOGE("no file");
		return;
	}

	int res = f->read(&header,sizeof(BasicWAVEHeader),1);

	getFormat();


	//this->riffCount = (header.dataSize/(header.bitsPerSample/8));
	//this->riffSize = header.dataSize / this->riffCount;


	//this->riffSize = (header.bitsPerSample/8)*header.channels;
	/*int count = Min(RIFF_COUNT, this->riffCount -curPos);
	this->datas[currentBuff] = readRiffs(count );

	if(!this->datas[currentBuff])
		return;

	createBufferFromWave(datas[currentBuff],this->riffSize*(count ), 0);
	GenSources();*/
	//LogHeaders();
	source = 0;


	alGenBuffers(BUFF_COUNT, buffers);
	alGenSources(1, &source);
	buf = (unsigned char *)malloc(BUFFER_SIZE);
/*
	LOGI("source %i",source);
	for(int i=0;i<BUFF_COUNT;++i)
		LOGI("buf [%i] = %i",i,buffers[i]);*/

	if(alGetError() != AL_NO_ERROR){
		LOGI("Error generating :(\n");
		return;
	}


	for(int i=0;i<BUFF_COUNT;++i)
		creatBuffer(i);

	if(alGetError() != AL_NO_ERROR) {
	  LOGI("Error loading :(\n");
	  return ;
	}



	alSourceQueueBuffers(source, BUFF_COUNT, buffers);
	if(alGetError() != AL_NO_ERROR) {
		  LOGI("Error alSourceQueueBuffers :(\n");
		  return;
	}


	/*int count = Min(BUFFER_SIZE, this->riffCount -curPos);
	this->datas[currentBuff] = readRiffs(count );

	if(!this->datas[currentBuff])
		return;

	createBufferFromWave(datas[currentBuff],this->riffSize*(count ), 0);
	GenSources();*/
}
void OALWav::loadWithoutStreaming(){
	unsigned  char * data = this->readWAVFull(f->getManager(), &header);

	getFormat();
	createBufferFromWave(data);
	GenSources();
}
void OALWav::load(AAssetManager *mgr, const char* filename){
	//this->mgr = mgr;
	//currentBuff = 0;
	//this->filename = filename;
	f = new AAssetFile(mgr, filename);
	this->buf = 0;
	if(!streaming)
		loadWithoutStreaming();
	else
		loadWithStreaming();



	this->LogHeaders();

}

void OALWav ::creatBuffer(int index){
	//int count = Min(BUFFER_SIZE, this->riffCount -curPos);
	//определям размер данных для чтения
	int size = Min(BUFFER_SIZE, header.dataSize -curPos);
	//this->datas[index] = readRiffs(size);
	//читаем чанки
	unsigned  char * data = readRiffs(size);
	if(!data)
		return;

	//создаём буферы
	createBufferFromWave(data,size, index);
	//GenSources(index);
}
