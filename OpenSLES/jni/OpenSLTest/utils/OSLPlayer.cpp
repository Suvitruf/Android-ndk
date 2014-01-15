#include "OSLPlayer.h"
#include <math.h>
bool OSLPlayer::isPlaying(){
	Log();
	return state() == SL_PLAYSTATE_PLAYING;
}
bool OSLPlayer::isPaused(){
	return state() == SL_PLAYSTATE_PAUSED;
}
bool OSLPlayer::isStopped(){
	return state() == SL_PLAYSTATE_STOPPED;
}
OSLPlayer::OSLPlayer(OSLContext * context){
		this->context = context;
		player = NULL;
		fdPlayerVolume = NULL;
		playerObj  = NULL;
		player  = NULL;
	}
void OSLPlayer::clear(){
	// destroy  audio player object, and invalidate all associated interfaces
	if (playerObj != NULL) {
		(*playerObj)->Destroy(playerObj);
		playerObj = NULL;
		player = NULL;
		fdPlayerVolume = NULL;
	}
}
OSLPlayer::~OSLPlayer(){
	clear();
}
SLuint32  OSLPlayer::state(){
	SLresult result;

	// make sure the URI audio player was created
	if (NULL != player) {

		SLuint32 state;

//		LOGD("state()");
		result = (*player)->GetPlayState(player, &state);
		assert(SL_RESULT_SUCCESS == result);

		return state;
	}

	return SL_PLAYSTATE_STOPPED;
}
//void OSLPlayer::clearLastSoundIfNeeded(OSLSound * sound){
//	if(this->sound != NULL){
////		if(this->sound != sound)
//			this->sound->clearPlayer();
////		else
////			LOGD("same sound");
//	}
//	else
//		LOGD("NULL sound");
//}
//float gain_to_attenuation( float gain ){
//    return 1000.0f * 20.0f * log10((double)gain);
//}
SLmillibel OSLPlayer::gain_to_attenuation(float gain) {

//	float v = 1000.0f * 20.0f * log10((double) gain);
	SLmillibel volume_mb;
	if (gain >= 3.0f)
		(*fdPlayerVolume)->GetMaxVolumeLevel(fdPlayerVolume, &volume_mb);
	else if (gain <= 0.02f)
		volume_mb = SL_MILLIBEL_MIN;
	else {
		volume_mb = M_LN2 / log(3.0f / (3.0f - gain)) * -1000.0f;
		if (volume_mb > 0)
			volume_mb = SL_MILLIBEL_MIN;
	}
//	LOGD("vol old = %f, new = %i", gain, volume_mb);
	return volume_mb;
}
float from_attenuation( float gain ){
    return pow(10, gain/ (1000.0f * 20.0f ));
}
void OSLPlayer::setVolume(float volume){
//	LOGD("hm %f", volume);
	SLresult result;
//	LOGD("defaq?");

//	SLVolumeItf volumeItf = getVolume();
	if ( fdPlayerVolume  != NULL) {
//		LOGD("why?");
		SLmillibel newVolume = gain_to_attenuation(volume);

		result = (*fdPlayerVolume)->SetVolumeLevel(fdPlayerVolume, newVolume);
//		LOGD("hm?");
		assert(SL_RESULT_SUCCESS == result);
	}
//	else{
//		LOGD("not?");
//	}
//	alSourcef(source, AL_GAIN, volume);
	//checkError();
}

float OSLPlayer::getVolume(){
//	LOGD("getVolume");
	SLresult result;
	SLmillibel millibel;
	result = (*fdPlayerVolume)->GetVolumeLevel(fdPlayerVolume, &millibel);
	return from_attenuation(millibel);

}
