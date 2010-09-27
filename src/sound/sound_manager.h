#ifndef _SOUND_
#define _SOUND_

//~ #ifndef WIN32
	#include <fmod/fmod.h>
//~ #endif

#include "../items/weapons.h"

#define MUSIC_CANAL 1
#define BABAR_FIRE_CANAL 2


class Sound_manager {
private:
	FSOUND_STREAM *m_music;
	FSOUND_SAMPLE *m_babar_jump;	
	FSOUND_SAMPLE *m_babar_rugissement;	
	FSOUND_SAMPLE **m_fire;
	FSOUND_SAMPLE *m_monster_damage;

public:
	Sound_manager();
	~Sound_manager();
	void play_music();
	void play_fire(int weapon);
	void play_babar_jump();
	void play_babar_rugissement();
	void play_monster_damage();
};


#endif
