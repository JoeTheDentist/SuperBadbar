#ifndef _SOUND_
#define _SOUND_

//~ #ifndef WIN32
	#include <fmod/fmod.h>
//~ #endif

#include "weapons.h"


class Sound_manager {
private:
	FSOUND_STREAM *m_music;
	FSOUND_SAMPLE **m_fire;
public:
	Sound_manager();
	~Sound_manager();
	void play_music();
	void play_fire(int weapon);
	
};


#endif
