
#include "OSLSound.h"
#include "unistd.h"

//
//unsigned int Min( unsigned int agr1,  unsigned int agr2){
//	return (agr1 <agr2) ?agr1 : agr2;
//}
OSLSound::~OSLSound(){

}
OSLSound::OSLSound( OSLContext * context, PlayerType playerType){
	this->context = context;
	this->mgr = context->mgr;
	player = NULL;
	volume = 1;
	loop = false;
	this->playerType = playerType;
	LOGD("	this->playerType = %i",	this->playerType);
}
//OSLSound::OSLSound( OSLContext * context, char * path){
//	this->context = context;
//	this->mgr = context->mgr;
//
//}
//OSLSound::~OSLSound()
//{
//
//}



void OSLSound::setOffset(float offset){
//    alSourcef(source, AL_SEC_OFFSET, offset);
    //checkError();
}
//float OSLSound::getOffset()
//{
//	float offset;
////	alGetSourcef(source, AL_SAMPLE_OFFSET, &offset );
//	return offset;
//
//    //alSourcef(source, AL_SEC_OFFSET, offset);
//    //checkError();
//}



//void OSLSound::setLooping(bool aBool){
//	alSourcei(source, AL_LOOPING, aBool ? AL_TRUE : AL_FALSE);
	//checkError();
//}
void OSLSound::setVolumePlayer(){
	if(player != NULL)
		if(player->sound != NULL && player->sound == this)
			player->setVolume(volume);

}
void OSLSound::setVolume(float volume){
//
//	LOGD("set volume %f", volume);
//	if(strstr(filename, "Fireball&SnowballWithDebrisV_1"))
//		LOGD("set %s volume %f ",filename, volume);

	this->volume = volume;
	if(player != NULL)
		setVolumePlayer();
}

float OSLSound::getVolume(){
//	LOGD("getvolume");
	return this->volume;
//	return player->getVolume();

}
void OSLSound::pause(){
//	LOGD("pause");
	if(player == NULL)
			return;
	player->pause();
}
void OSLSound::setLoop(bool loop){
	this->loop = loop;
}

bool OSLSound::isLooping(){
	return this->loop;
}

//void OSLSound::clearPlayer(){
//	LOGD("cleared1");
//	player = NULL;
//	LOGD("cleared2");
//}
void OSLSound::play(){
//	LOGD("play");
	if(	player != NULL && player->isPaused()){
		setVolumePlayer();
		player->play();
		return;
	}


	player = context->getFreePlayer(this);
	LOGD("set %s",filename);


	if(	player == NULL){
//		LOGD("	player is null");
		return;
	}


	player->setSound(this);
//	LOGD("here?");
//	player->setBuffer(buf,dataSize);
	setVolumePlayer();
//	LOGD("here2 ?");
	if(	player != NULL)
		player->play();
}
void OSLSound::rewind(){
//	alSourceRewind(source);
	//checkError();
}

void OSLSound::stop(){
//	LOGD("stop %s",filename);
	if(player == NULL)
		return;
//	LOGD("stop? %s",filename);
	player->stop();
	player = 0;
}

SLuint32 OSLSound::state(){
//	LOGD("state");
	if(player == NULL)
		return SL_PLAYSTATE_STOPPED;
	return  player->state();
}

bool OSLSound::isActive(){
//	LOGD("state");
	int newState = state();
	return !(newState == SL_PLAYSTATE_STOPPED);
}

//bool OSLSound::isInitializing(){
////	return state() == AL_INITIAL;
//}

bool OSLSound::isPlaying(){
//	LOGD("state");
	return state() == SL_PLAYSTATE_PLAYING;
}

bool OSLSound::isPaused(){
//	LOGD("state");
	return state() == SL_PLAYSTATE_PAUSED;
}

bool OSLSound::isStopped(){
//	LOGD("state");
	return state() == SL_PLAYSTATE_STOPPED;
}





