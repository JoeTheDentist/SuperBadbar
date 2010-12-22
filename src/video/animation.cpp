/**
 * 	@file animation.cpp
 * 	@brief Impl√©mentation de la classe Animation
 *
 * 	@author Guillaume B√©rard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "animation.h"
#include "../video/surface.h"


Animation::Animation(std::string * s, int size, bool force) {
    m_images = new Surface*[size];
    m_size = size;
    m_curr = 0;
    m_phase = 0;
    m_force = force;

    for (int i=0;i<size;i++) {
        m_images[i] = new Surface(s[i]);
    }

    if ( m_force ) {
        m_finished = false;
    } else {
        m_finished = true;
    }
}

Animation::~Animation() {
    for (int i=0;i<m_size;i++) {
        delete m_images[i];
    }
    delete[] m_images;
}

Surface * Animation::curr_pic() 
{
    Surface *image = m_images[m_curr];
    m_phase++;
    m_phase%=ANIMATION_SPEED;

    if ( m_phase == 0 ) {
        if ( m_force && m_finished ) {  /* si on a fini en forcÈ, on garde toujours la derniere image */
            m_curr = m_size-1;
        } else {                        /* sinon on affiche les images cycliquement */
            m_curr++;
            m_curr%=m_size;
        }

        if ( m_force && ( m_curr == 0 ) ) { /* une fois qu'on a fini une animation en forcÈ, on a fini */
            m_finished = true;
        }
    }

    return image;
}

bool Animation::interruptable() 
{
    return m_finished;
}

void Animation::setRect(Rect &pos)
{
    pos.h = m_images[m_curr]->h();
    pos.w = m_images[m_curr]->w();
}
