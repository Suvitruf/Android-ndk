#include "OSLBufferPlayer.h"

OSLBufferPlayer::OSLBufferPlayer(OSLContext * context):OSLPlayer(context){
//	player = NULL;
//	fdPlayerVolume = NULL;
//	playerObj  = NULL;
//	player  = NULL;
	init();
//	lastSound = 0;
}
SLuint32 OSLBufferPlayer::state(){
	SLresult result;
	if (NULL != player && bufferQueue != NULL) {

		SLBufferQueueState state;

//		LOGD("state()");
		result = (*bufferQueue)->GetState(bufferQueue, &state);
		assert(SL_RESULT_SUCCESS == result);

//		LOGD("count = %i, playIndex = %i", state.count, state.playIndex);
		SLuint32 statePlayer;
		result = (*player)->GetPlayState(player, &statePlayer);
		if(statePlayer == SL_PLAYSTATE_PLAYING)
			if(state.count == 0)
				return SL_PLAYSTATE_STOPPED;

		return statePlayer;
//		return this->state();
//		return state();
	}
	return SL_PLAYSTATE_STOPPED;
}
void OSLBufferPlayer::Log(){
	SLresult result;

	// make sure the URI audio player was created
	if (NULL != player) {

		SLBufferQueueState state;

//		LOGD("state()");
		result = (*bufferQueue)->GetState(bufferQueue, &state);
		assert(SL_RESULT_SUCCESS == result);

//		LOGD("count = %i, playIndex = %i", state.count, state.playIndex);
	}

}
OSLBufferPlayer::~OSLBufferPlayer(){
	bufferQueue = NULL;
}

//void PlayEventCallback( SLPlayItf caller,  void *pContext, SLuint32 event){
//	if(((OSLBufferPlayer*)pContext)->isPlaying())
//		((OSLBufferPlayer*)pContext)->stop();
//	LOGD("event %s", ((OSLBufferPlayer*)pContext)->lastSound->filename);
//	((OSLBufferPlayer*)pContext)->setSound(((OSLBufferPlayer*)pContext)->lastSound);
//	((OSLBufferPlayer*)pContext)->stop();
//	((OSLBufferPlayer*)pContext)->play();
//	LOGD("event %s", ((OSLBufferPlayer*)pContext)->lastSound->filename);
//	((OSLBufferPlayer*)pContext)->replaySound();
//	(*caller)->SetPlayState(caller, SL_PLAYSTATE_PLAYING);
//	((OSLBufferPlayer*)pContext)->play();
//}

void OSLBufferPlayer::init(){
	SLresult result;

//	locatorBufferQueue = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 1}; /*���� ����� � �������*/
	SLDataLocator_AndroidSimpleBufferQueue locatorBufferQueue;
	locatorBufferQueue.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
	locatorBufferQueue.numBuffers = 16;

//	formatPCM = {
//		SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_22_05,
//		SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
//		SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN
//	};

	SLDataFormat_PCM formatPCM;
	formatPCM.formatType = SL_DATAFORMAT_PCM;
	formatPCM.numChannels = 2;
	formatPCM.samplesPerSec = SL_SAMPLINGRATE_44_1;// header.samplesPerSec*1000;
	formatPCM.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16 ;//header.bitsPerSample;
	formatPCM.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;// header.fmtSize;
	formatPCM.channelMask = SL_SPEAKER_FRONT_LEFT|SL_SPEAKER_FRONT_RIGHT ;
	formatPCM.endianness = SL_BYTEORDER_LITTLEENDIAN;

//	audioSrc = {&locatorBufferQueue, &formatPCM};
	audioSrc.pLocator = &locatorBufferQueue;
	audioSrc.pFormat = &formatPCM;
//	 locatorOutMix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObj};
//	locatorOutMix = {SL_DATALOCATOR_OUTPUTMIX, context->getOutputMixObject()};
	locatorOutMix.locatorType = SL_DATALOCATOR_OUTPUTMIX;
	locatorOutMix.outputMix =  context->getOutputMixObject();
//	audioSnk = {&locatorOutMix, NULL};
	audioSnk.pLocator = &locatorOutMix;
	audioSnk.pFormat = NULL;
//	pIDs[1] = {SL_IID_BUFFERQUEUE};
//	pIDsRequired[1] = {SL_BOOLEAN_TRUE};
	 // create audio player
	const SLInterfaceID ids[2] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE,/*SL_IID_MUTESOLO,*/
			/*SL_IID_EFFECTSEND,SL_IID_SEEK,*/
			/*SL_IID_MUTESOLO,*/ SL_IID_VOLUME};
	const SLboolean req[2] = {SL_BOOLEAN_TRUE,SL_BOOLEAN_TRUE};

	result = (*context->getEngine())->CreateAudioPlayer(context->getEngine(),
			&playerObj, &audioSrc, &audioSnk,2, ids, req);

	assert(SL_RESULT_SUCCESS == result);

	result = (*playerObj)->Realize(playerObj, SL_BOOLEAN_FALSE );
	assert(SL_RESULT_SUCCESS == result);
	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Can not CreateAudioPlayer %d", result);
		playerObj = NULL;

	}


	result = (*playerObj)->GetInterface(playerObj, SL_IID_PLAY, &player);
	assert(SL_RESULT_SUCCESS == result);



	// get the seek interface
//	result = (*playerObj)->GetInterface(playerObj, SL_IID_SEEK, &fdPlayerSeek);
//	assert(SL_RESULT_SUCCESS == result);

	// get the mute/solo interface
//	result = (*playerObj)->GetInterface(playerObj, SL_IID_MUTESOLO, &fdPlayerMuteSolo);
//	assert(SL_RESULT_SUCCESS == result);

	// get the volume interface
	result = (*playerObj)->GetInterface(playerObj, SL_IID_VOLUME, &fdPlayerVolume);
	assert(SL_RESULT_SUCCESS == result);


	result = (*playerObj)->GetInterface(playerObj,       SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &bufferQueue);
	assert(SL_RESULT_SUCCESS == result);


//	result = (*player)->RegisterCallback(player, PlayEventCallback, (void *) &context);
//	result = (*player)->RegisterCallback(player, PlayEventCallback, (void *) this);
//	assert(SL_RESULT_SUCCESS == result);
//	result =(*player)->SetCallbackEventsMask(player, SL_PLAYEVENT_HEADATEND);
//	assert(SL_RESULT_SUCCESS == result);
}

//void OSLBufferPlayer::setVolume(float volume){
//
//	SLresult result;
////	SLVolumeItf volumeItf = getVolume();
//	if (NULL != fdPlayerVolume) {
//		result = (*fdPlayerVolume)->SetVolumeLevel(fdPlayerVolume, volume);
//		assert(SL_RESULT_SUCCESS == result);
//	}
////	alSourcef(source, AL_GAIN, volume);
//	//checkError();
//}
//
//float OSLBufferPlayer::getVolume(){
//	SLresult result;
//	SLmillibel millibel;
//	result = (*fdPlayerVolume)->GetVolumeLevel(fdPlayerVolume, &millibel);
//	return millibel;
//
//}


void OSLBufferPlayer::pause(){
//	LOGD("pause");
	if( player == NULL) return;
	SLresult result;

	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_PAUSED);
	assert(SL_RESULT_SUCCESS == result);
}
//void OSLBufferPlayer::setBuffer(char * buf, long dataSize){
//	(*bufferQueue)->Clear(bufferQueue);
//	(*bufferQueue)->Enqueue(bufferQueue, buf, dataSize);
//}
void OSLBufferPlayer::setSound(OSLSound * sound){

	if(bufferQueue == NULL)
		LOGD("bufferQueue is null");


	this->sound = sound;

	(*bufferQueue)->Clear(bufferQueue);
	(*bufferQueue)->Enqueue(bufferQueue, sound->getBuffer() , sound->getSize());

}
//void OSLBufferPlayer::replaySound(){
//
//	if(lastSound != NULL){
//		LOGD("1 %s size %i",lastSound->filename, lastSound->getSize());
////		stop();
//		LOGD("2 %s size %i",lastSound->filename, lastSound->getSize());
//		if(lastSound->getBuffer() == NULL)
//			LOGD("buf null");
//		if(bufferQueue == NULL)
//			LOGD("bufferQueue null");
//		//(*bufferQueue)->Clear(bufferQueue); /*������� ������� �� ������, ���� ��� ���-�� ����. ����� ��������, ���� �������, ����� ������� ������� ���� ��������*/
//		(*bufferQueue)->Enqueue(bufferQueue, lastSound->getBuffer() , lastSound->getSize());
//		LOGD("3 %s size %i",lastSound->filename, lastSound->getSize());
//		play();
//		LOGD("4 %s size %i",lastSound->filename, lastSound->getSize());
//	}
//	else{
//		LOGD("null");
//	}
////	this->play();
//}
void OSLBufferPlayer::play(){
//	LOGD("play");
	if( player == NULL) return;
	SLresult result;
	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
	assert(SL_RESULT_SUCCESS == result);
}

void OSLBufferPlayer::stop(){
//	LOGD("stop");
	if( player == NULL) return;
	SLresult result;
	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_STOPPED);
//	initBuf();
	assert(SL_RESULT_SUCCESS == result);
//	lastSound = 0;
}

//SLuint32 OSLBufferPlayer::state(){
//	SLresult result;
//
//	// make sure the URI audio player was created
//	if (NULL != player) {
//
//		SLuint32 state;
////		LOGD("state()");
//		result = (*player)->GetPlayState(player, &state);
//		assert(SL_RESULT_SUCCESS == result);
//
//		return state;
//	}
//
//	return 0;
//}

//bool OSLBufferPlayer::isPlaying(){
//	return state() == SL_PLAYSTATE_PLAYING;
//}
//bool OSLBufferPlayer::isPaused(){
//	return state() == SL_PLAYSTATE_PAUSED;
//}
//bool OSLBufferPlayer::isStopped(){
//	return state() == SL_PLAYSTATE_STOPPED;
//}
