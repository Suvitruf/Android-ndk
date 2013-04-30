#include "OALOgg.h"

OALOgg::OALOgg():OALSound()
{

}

OALOgg::~OALOgg()
{
	ov_clear(&vf);
}


unsigned int suiCurrPos = 0;
unsigned int suiSize = 0;

static size_t  read_func(void* ptr, size_t size, size_t nmemb, void* datasource)
{
    unsigned int uiBytes = Min(suiSize - suiCurrPos, (unsigned int)nmemb * (unsigned int)size);
    memcpy(ptr, (unsigned char*)datasource + suiCurrPos, uiBytes);
    suiCurrPos += uiBytes;

    return uiBytes;
}

static int seek_func(void* datasource, ogg_int64_t offset, int whence)
{
    if (whence == SEEK_SET)
        suiCurrPos = (unsigned int)offset;
    else if (whence == SEEK_CUR)
        suiCurrPos = suiCurrPos + (unsigned int)offset;
    else if (whence == SEEK_END)
        suiCurrPos = suiSize;

    return 0;
}

static int close_func(void* datasource)
{
    return 0;
}

static long tell_func(void* datasource)
{
    return (long)suiCurrPos;
}
void OALOgg::Log(){
	LOGI("vi->channels = %i",vi->channels);
	LOGI("vi->rate = %i",vi->rate);
	LOGI("vi->version = %i",vi->version);
}
void OALOgg::getInfo(unsigned int uiOggSize, char* pvOggBuffer){
	// Заменяем колбэки
	    ov_callbacks callbacks;
	    callbacks.read_func = &read_func;
	    callbacks.seek_func = &seek_func;
	    callbacks.close_func = &close_func;
	    callbacks.tell_func = &tell_func;


	    suiCurrPos = 0;
	    suiSize = uiOggSize;
	    int iRet = ov_open_callbacks(pvOggBuffer, &vf, NULL, 0, callbacks);

	    // Заголовки
	    vi = ov_info(&vf, -1);

	    uiPCMSamples = (unsigned int)ov_pcm_total(&vf, -1);
}
void * OALOgg::ConvertOggToPCM(unsigned int uiOggSize, char* pvOggBuffer)
{
	if(suiSize == 0){
		getInfo( uiOggSize, pvOggBuffer);
		current_section = 0;
		iRead = 0;
		uiCurrPos = 0;
	}



    void* pvPCMBuffer = malloc(uiPCMSamples * vi->channels * sizeof(short));

    // Декодим
    do
    {
        iRead = ov_read(&vf, (char*)pvPCMBuffer + uiCurrPos, 4096, &current_section);
        uiCurrPos += (unsigned int)iRead;
    }
    while (iRead != 0);

    return pvPCMBuffer;
}

void OALOgg::load(AAssetManager *mgr, const char* filename){
	this->filename = filename;
	char* buf = 0;
	AAssetFile f = AAssetFile(mgr, filename);
	if (f.null()) {
		LOGE("no file %s in readOgg",filename);
		return ;
	}

	buf = 0;
	buf = (char*)malloc(f.size());
	if (buf){
		if(f.read(buf,f.size(),1)){
		}
		else {
			free(buf);
			f.close();
			return;
		}
	}

	//LOGI("f.size() = %i",f.size());
	//PreConvert(f.size(),buf);
	char * data = (char *)ConvertOggToPCM(f.size(),buf);
	f.close();

	 if (vi->channels == 1)
	    format = AL_FORMAT_MONO16;
	  else
	    format = AL_FORMAT_STEREO16;

	alGenBuffers(1,&buffer);
	//LOGI("uiPCMSamples = %i", uiPCMSamples);
	//Log();
	//LOGI("sizeof(short) = %i",sizeof(short));
	//LOGI("Size = %u",uiPCMSamples * vi->channels * sizeof(short));

	alBufferData(buffer,format,data,uiPCMSamples * vi->channels * sizeof(short),vi->rate);

	source = 0;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
}


void OALOgg::play(){



	if(!streaming){

		alSourcePlay(source);

		do {} while(isPlaying());
	}
}
