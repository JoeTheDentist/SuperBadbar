#include <SDL/SDL.h>
#include <stdint.h>

#include "animations.h"

Animation::Animation()
{
    m_nb_pics = 1;
    m_curr_pic = 0;
    m_pics = new SDL_Surface*[m_nb_pics];
}

Animation::Animation(uint8_t nb_pics, SDL_Surface **pics)
{
    m_curr_pic = 0;
    m_nb_pics = nb_pics;
    m_pics = pics;
}

Animation::~Animation()
{
//~     delete[] m_pics;
}

uint8_t Animation::nb_pics()
{
    return m_nb_pics;
}

SDL_Surface *Animation::current_pic()
{
    return m_pics[m_curr_pic];
}

void Animation::next_pic()
{
    m_curr_pic = (m_curr_pic+1)%m_nb_pics;
}
