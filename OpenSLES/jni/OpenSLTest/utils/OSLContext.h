#ifndef _OSLContext_
#define _OSLContext_

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
//#include <OSLBufferPlayer.h>
#include <OSLPlayer.h>

#include <OSLSound.h>
//#include "def.h"
//class OSLPlayer;
class OSLSound;


#define MAX_BUF_PLAYERS_COUNT 8
#define MAX_ASSET_PLAYERS_COUNT 16
class OSLContext
{
private:
	void initPlayers();

//	SLInterfaceID pIDs[1];// = {SL_IID_ENGINE};
//	SLboolean pIDsRequired[1];//  = {SL_BOOLEAN_TRUE};
//    static const SLuint32 lEngineMixIIDCount = 1;
	SLEngineItf engine;
	SLObjectItf engineObj;
    SLObjectItf outputMixObj;
//    SLuint32 lOutputMixIIDCount;
//    SLInterfaceID lOutputMixIIDs[];// = {};
//    SLboolean lOutputMixReqs[] ;//= {};
    OSLPlayer * bufPlayers[MAX_BUF_PLAYERS_COUNT];
    OSLPlayer * assetPlayers[MAX_ASSET_PLAYERS_COUNT];
//    SLresult result;
public:
    void pause();
    void resume();
//    void playBuffer(char*  buf, long size);
    OSLPlayer * getFreePlayer(OSLSound * sound);
	OSLContext (AAssetManager *mgr);
	~OSLContext ();
	AAssetManager *mgr;
	SLObjectItf getOutputMixObject(){
		return outputMixObj;
	}
//	SLresult getSLResult(){
//		return result;
//	}
	SLEngineItf getEngine(){
		return engine;
	}

};

#endif
