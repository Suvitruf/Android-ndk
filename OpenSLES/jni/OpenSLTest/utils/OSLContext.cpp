#include "OSLContext.h"
#include "stddef.h"
#include <OSLAssetPlayer.h>
#include <OSLBufferPlayer.h>

OSLContext::OSLContext(AAssetManager *mgr){
	LOGD("oslContext");
	this->mgr = mgr;
	SLresult result;
//	pIDs[1] = {SL_IID_ENGINE};
//	pIDsRequired[1]  = {SL_BOOLEAN_TRUE};
//	result = slCreateEngine(
//	    &engineObj, /*Указатель на результирующий объект*/
//	    0, /*Количество элементов в массиве дополнительных опций*/
//	    NULL, /*Массив дополнительных опций, NULL, если они Вам не нужны*/
//	    lEngineMixIIDCount, /*Количество интерфесов, которые должен будет поддерживать создаваемый объект*/
//	    pIDs, /*Массив ID интерфейсов*/
//	pIDsRequired /*Массив флагов, указывающих, необходим ли соответствующий интерфейс. Если указано SL_TRUE, а интерфейс не поддерживается, вызов завершится неудачей, с кодом возврата SL_RESULT_FEATURE_UNSUPPORTED*/
//	);
	const SLuint32 lEngineMixIIDCount = 1;
	const SLInterfaceID lEngineMixIIDs[] = {SL_IID_ENGINE};
	const SLboolean lEngineMixReqs[] = {SL_BOOLEAN_TRUE};
	const SLuint32 lOutputMixIIDCount = 0;
	const SLInterfaceID lOutputMixIIDs[] = {};
	const SLboolean lOutputMixReqs[] = { };

	result = slCreateEngine(&engineObj, 0, NULL, lEngineMixIIDCount,
			lEngineMixIIDs, lEngineMixReqs);

	/*Проверяем результат. Если вызов slCreateEngine завершился неуспехом – ничего не поделаешь*/
	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after slCreateEngine");
		return;
	}

	result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE );

	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after Realize");
		return;
	}

	result = (*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engine);

	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after GetInterface");
		return;
	}

	result = (*engine)->CreateOutputMix(engine, &outputMixObj,
			lOutputMixIIDCount, lOutputMixIIDs, lOutputMixReqs);

	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after CreateOutputMix");
		return;
	}

	result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE );

	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after Realize");
		return;
	}


	result = (*engine)->CreateOutputMix(engine, &outputMixObj, lOutputMixIIDCount, lOutputMixIIDs, lOutputMixReqs);

	if(result != SL_RESULT_SUCCESS){
			LOGE("Error after CreateOutputMix");
			return;
	}

	result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE);

	if(result != SL_RESULT_SUCCESS){
			LOGE("Error after Realize");
			return;
	}


	initPlayers();

}

OSLContext::~OSLContext(){
	for(int i = 0; i< MAX_BUF_PLAYERS_COUNT; ++i)
		delete bufPlayers[i];

	for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i)
		delete assetPlayers[i];

	// destroy output mix object, and invalidate all associated interfaces
	if (outputMixObj != NULL) {
		(*outputMixObj)->Destroy(outputMixObj);
		outputMixObj = NULL;
	}

	// destroy engine object, and invalidate all associated interfaces
	if (engine != NULL) {
		(*engineObj)->Destroy(engineObj);
		engineObj = NULL;
		engine = NULL;
	}

}
void OSLContext::initPlayers(){
	for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i)
		assetPlayers[i] = new OSLAssetPlayer(this);

	for(int i = 0; i< MAX_BUF_PLAYERS_COUNT; ++i)
			bufPlayers[i] = new OSLBufferPlayer(this);

}

void OSLContext::resume(){
	for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i){
		if(assetPlayers[i]->isPaused()){
			assetPlayers[i]->play();
		}
	}
	for(int i = 0; i< MAX_BUF_PLAYERS_COUNT; ++i){
		if(bufPlayers[i]->isPaused()){
			bufPlayers[i]->play();
		}
	}
}

void OSLContext::pause(){
	for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i){
		if(assetPlayers[i]->isPlaying()){
			assetPlayers[i]->pause();
		}
	}
	for(int i = 0; i< MAX_BUF_PLAYERS_COUNT; ++i){
		if(bufPlayers[i]->isPlaying()){
			bufPlayers[i]->pause();
		}
	}
}
OSLPlayer * OSLContext::getFreePlayer(OSLSound * sound){
//	LOGD("getFreePlayer");
	if(sound->isLooping()){
		for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i){
			if(!assetPlayers[i]->isPlaying()){
//				LOGD("getAssetPlayer = %i", i);

				return assetPlayers[i];
			}
		}
		return assetPlayers[0];
	}
	else{
		for(int i = 0; i< MAX_BUF_PLAYERS_COUNT; ++i){

			if(!bufPlayers[i]->isPlaying()){
//				LOGD("getBufPlayer = %i", i);

				return bufPlayers[i];
			}

		}
		return bufPlayers[0];

	}
//	return players[0];
}
