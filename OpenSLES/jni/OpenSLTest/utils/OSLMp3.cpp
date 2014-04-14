#include "OSLMp3.h"
#include <assert.h>

// me don't have our own decoder method for mp3, so for playing mp3 we can use only AssetPlayer
OSLMp3::OSLMp3(OSLContext * context):OSLSound(context, AASSET){
	setLoop(true);
}
OSLMp3::OSLMp3( OSLContext * context,  char * path):OSLSound(context, AASSET){
	load(path);
}
OSLMp3::~OSLMp3(){

}


void OSLMp3::load(char* filename) {
	strcpy(this->filename, filename);
	/*
	 * Here we can load mp3 from file using some lib.
	 * But for mp3 i using always AssetPlayer, so no need to read full file to memory. But, if you want, you can use, for example:
	 * MAD (MPEG Audio Decoder) http://sourceforge.net/projects/mad/
	 * LAME http://lame.sourceforge.net/
	 */
}
