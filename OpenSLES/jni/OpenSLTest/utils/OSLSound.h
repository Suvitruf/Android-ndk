#ifndef _OSLSound_
#define _OSLSound_

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "OSLContext.h"

class OSLPlayer;
class OSLSound;
class OSLContext;

class OSLSound
{


public:
	enum PlayerType {BUFFER, AASSET};

	PlayerType playerType;
	char filename[64];
	virtual void load(char * path) = 0;

	virtual ~OSLSound();
	OSLSound( OSLContext * context, PlayerType playerType);
//	OSLSound( OSLContext * context, char * path);

	virtual void setVolume(float volume);
	virtual float getVolume();
//	void setLooping(bool looping);

	virtual void play();
	virtual void pause();
	void rewind();
	virtual void stop();
	SLuint32 state();

	bool isActive();
//	bool isInitializing();
	virtual bool isPlaying();
	virtual bool isPaused();
	virtual bool isStopped();
    void setOffset(float offset);
    void setLoop(bool loop);
//    virtual float getOffset();
//    virtual void load( char* filename)= 0;
//    virtual AAsset* openFile(char * path) = 0;
    bool isLooping();
    virtual long getSize() { return 0; }
    virtual char * getBuffer() { return 0; }

    PlayerType getPlayerType(){ return playerType; }
//    void clearPlayer();
protected:
    bool loop;
    float volume;
    void setVolumePlayer();
    OSLPlayer * player;
    AAssetManager *mgr;
	OSLContext * context;



//    virtual void initBuf() = 0;

private:

};

#endif
