#include "OSLAssetPlayer.h"
extern AAssetManager *mgr;
OSLAssetPlayer::OSLAssetPlayer(OSLContext * context):OSLPlayer(context){
//	this->context = context;
//	init();
//	lastSound = 0;
}
OSLAssetPlayer::~OSLAssetPlayer(){

	clear();
}
void OSLAssetPlayer::clear(){
	fdPlayerSeek = NULL;
	fdPlayerMuteSolo = NULL;
}
void OSLAssetPlayer::init(char * filename){

	SLresult result;

	AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_UNKNOWN);

	// the asset might not be found
//	if (NULL == asset) {
//		return JNI_FALSE;
//	}

	// open asset as file descriptor
	off_t start, length;
	int fd = AAsset_openFileDescriptor(asset, &start, &length);
	assert(0 <= fd);
	AAsset_close(asset);

	// configure audio source
	SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
	SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
	SLDataSource audioSrc = {&loc_fd, &format_mime};

	// configure audio sink
	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX,  context->getOutputMixObject()};
	SLDataSink audioSnk = {&loc_outmix, NULL};

	// create audio player
	const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
	const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
	result = (*context->getEngine())->CreateAudioPlayer(context->getEngine(), &playerObj, &audioSrc, &audioSnk,
			3, ids, req);
	assert(SL_RESULT_SUCCESS == result);

	// realize the player
	result = (*playerObj)->Realize(playerObj, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the play interface
	result = (*playerObj)->GetInterface(playerObj, SL_IID_PLAY, &player);
	assert(SL_RESULT_SUCCESS == result);

	// get the seek interface
	result = (*playerObj)->GetInterface(playerObj, SL_IID_SEEK, &fdPlayerSeek);
	assert(SL_RESULT_SUCCESS == result);

	// get the mute/solo interface
	result = (*playerObj)->GetInterface(playerObj, SL_IID_MUTESOLO, &fdPlayerMuteSolo);
	assert(SL_RESULT_SUCCESS == result);

	// get the volume interface
	result = (*playerObj)->GetInterface(playerObj, SL_IID_VOLUME, &fdPlayerVolume);
	assert(SL_RESULT_SUCCESS == result);

	// enable whole file looping
	result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, sound->isLooping() ? SL_BOOLEAN_TRUE : SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
	assert(SL_RESULT_SUCCESS == result);

//	return JNI_TRUE;
}

void OSLAssetPlayer::setSound(OSLSound * sound){

	this->sound = sound;
	clear();
	OSLPlayer::clear();
	init(sound->filename);
}

void OSLAssetPlayer::pause(){
	if( player == NULL) return;
	SLresult result;

	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_PAUSED);
	assert(SL_RESULT_SUCCESS == result);
}
void OSLAssetPlayer::play(){

	if( player == NULL) return;
	SLresult result;
	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
	assert(SL_RESULT_SUCCESS == result);
}
void OSLAssetPlayer::stop(){
	if( player == NULL) return;
	SLresult result;
	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_STOPPED);
//	initBuf();
	assert(SL_RESULT_SUCCESS == result);
//	lastSound = 0;
}
