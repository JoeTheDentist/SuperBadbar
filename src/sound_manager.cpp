
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include "sound_manager.h"
#include "debug.h"



Sound_manager::Sound_manager()
{
	FSOUND_Init(44100, 32, 0);
	m_fire = new FSOUND_SAMPLE*[MACHINEGUN + 1];
	m_music = FSOUND_Stream_Open("../sound/music/level1.mp3", 0, 0, 0);
	if (m_music == NULL) {
		PRINT_DEBUG(1, "Impossible de charger la musique")
	}
	m_fire[MACHINEGUN] =  FSOUND_Sample_Load(FSOUND_FREE, "../sound/weapons/machingun.wav", 0, 0, 0);
	m_fire[SHOTGUN] =  FSOUND_Sample_Load(FSOUND_FREE, "../sound/weapons/shotgun.wav", 0, 0, 0);

}




Sound_manager::~Sound_manager()
{
	FSOUND_Close();
	
}


void Sound_manager::play_music()
{
	FSOUND_Stream_Play(FSOUND_FREE, m_music);
}


void Sound_manager::play_fire(int weapon)
{
	 FSOUND_PlaySound(FSOUND_FREE, m_fire[weapon]);
	
}
