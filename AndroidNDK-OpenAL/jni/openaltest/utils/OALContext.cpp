#include "OALContext.h"



OALContext::OALContext()
{

	device = alcOpenDevice(0);
	//const ALint context_attribs[] = { ALC_FREQUENCY, 22050, 0 };
	context = alcCreateContext(device, 0);
	//checkError();
	//if (context)
		alcMakeContextCurrent(context);
	process();
}

OALContext::~OALContext()
{
	alcMakeContextCurrent(0);
	alcMakeContextCurrent(0);
	if (context) alcDestroyContext(context);
	alcCloseDevice(device);
	//delete device;
}


void OALContext::process()
{
	alcProcessContext(context);
	//checkError();
}

void OALContext::suspend()
{
	alcSuspendContext(context);
	//checkError();
}

ALCdevice * OALContext::getAlcDevice()
{
	return alcGetContextsDevice(context);
}

void OALContext::setDevice(ALCdevice *device)
{
	this->device = device;
}
