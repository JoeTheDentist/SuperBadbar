
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include "sound_manager.h"
#include "../util/debug.h"



Sound_manager::Sound_manager()
{
	FSOUND_Init(44100, 32, 0);
	m_fire = new FSOUND_SAMPLE*[SHOTGUN + 1];
	m_music = FSOUND_Stream_Open("../sound/music/level1.mp3", 0, 0, 0);
	if (m_music == NULL) {
		PRINT_DEBUG(1, "Impossible de charger la musique")
	}
	m_fire[MACHINEGUN] =  FSOUND_Sample_Load(FSOUND_FREE, "../sound/weapons/machingun.wav", 0, 0, 0);
	m_fire[GUN] =  FSOUND_Sample_Load(FSOUND_FREE, "../sound/weapons/machingun.wav", 0, 0, 0);

	m_fire_shotgun = FSOUND_Sample_Load(FSOUND_FREE, "../sound/weapons/shotgun.wav", 0, 0, 0);
	m_fire[SHOTGUN] =  FSOUND_Sample_Load(FSOUND_FREE, "../sound/weapons/shotgun.wav", 0, 0, 0);
	m_babar_jump = FSOUND_Sample_Load(FSOUND_FREE, "../sound/babar/jump.mp3", 0, 0, 0);
	m_monster_damage = FSOUND_Sample_Load(FSOUND_FREE, "../sound/monsters/kickass.mp3", 0, 0, 0);
	FSOUND_SetPan(BABAR_FIRE_CANAL, 5);
	FSOUND_SetVolume(BABAR_FIRE_CANAL, 5);
}




Sound_manager::~Sound_manager()
{
	FSOUND_Close();
	
}


void Sound_manager::play_music()
{
	FSOUND_Stream_Play(MUSIC_CANAL, m_music);
}


void Sound_manager::play_fire(int weapon)
{
		 if(!FSOUND_SetVolume(BABAR_FIRE_CANAL, 0)){
			 PRINT_DEBUG(1, "IMPOSSIBLE")
		 }

	int channel = FSOUND_PlaySound(BABAR_FIRE_CANAL, m_fire[weapon]);
	FSOUND_SetVolume(channel, 100);
	
}

void Sound_manager::play_babar_jump()
{
	FSOUND_PlaySound(4, m_babar_jump);

}

void Sound_manager::play_monster_damage()
{
	FSOUND_PlaySound(5, m_monster_damage);

}


