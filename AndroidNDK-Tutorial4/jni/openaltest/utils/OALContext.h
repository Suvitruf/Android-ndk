#include <al.h>
#include <alc.h>

class OALContext
{
	ALCdevice* device;
	ALCcontext* context;
public:
	OALContext ();
	~OALContext ();

	void process();
	void suspend();

	ALCdevice * getAlcDevice();
	void setDevice(ALCdevice *newDevice);
};
