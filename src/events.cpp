
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "events.h"

Events_status::Events_status()
{
    /* Rappel : le fait de pouvoir detecter plusieurs touches d�pends des touches elles m�mes... */
	for (uint32_t i = 0; i < SDLK_LAST; i++)
		m_key_config[i] = k_none;
	for (uint32_t i = 0; i <= k_fire; i++)
		m_key_down[i] = false;
	m_key_config[SDLK_i] = k_up;
	m_key_config[SDLK_k] = k_down;
	m_key_config[SDLK_j] = k_left;
	m_key_config[SDLK_l] = k_right;
	m_key_config[SDLK_SPACE] = k_jump;
	m_key_config[SDLK_w] = k_fire;
}
Events_status::~Events_status()
{

}


void Events_status::update_events()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT :
			m_key_down[k_exit]=1;
			break;
		case SDL_KEYDOWN:
			m_key_down[m_key_config[event.key.keysym.sym]]=1;
			if (event.key.keysym.sym==SDLK_ESCAPE) {
			    m_key_down[k_exit]=1;
			}
			break;
		case SDL_KEYUP:
			m_key_down[m_key_config[event.key.keysym.sym]]=0;
			break;
		default:
			break;
		}
	}
}

bool Events_status::key_down(enum key k)
{
	return m_key_down[k];
}

bool Events_status::key_dir_down()
{
    return (m_key_down[k_left]||m_key_down[k_right]);
}
