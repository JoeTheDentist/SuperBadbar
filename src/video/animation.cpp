/**
 * 	@file animation.cpp
 * 	@brief Impl√©mentation de la classe Animation
 *
 * 	@author Guillaume B√©rard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <stdint.h>

#include "animation.h"
#include "../video/surface.h"


Animation::Animation(std::string * s, int size, anim_type type) {
    m_images = new Surface*[size];
    m_size = size;
    m_curr = 0;
    m_phase = 0;

    for (int i=0;i<size;i++) {
        m_images[i] = new Surface(s[i]);
    }

    m_type = type;

    if ( type == CYCLE ) {
        m_finished = true;
    } else {
        m_finished = false;
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
        if ( m_type != CYCLE && m_finished ) {  /* si on a fini sans Ítre en CYCLE, on garde la derniËre image */
            m_curr = m_size-1;
        } else {                        /* sinon on affiche les images cycliquement */
            m_curr++;
            m_curr%=m_size;
        }

        if ( m_type != CYCLE && ( m_curr == 0 ) ) { /* une fois qu'on a fini une animation en forcÈ, on a fini */
            m_finished = true;
        }
    }
    return image;
}

bool Animation::interruptable()
{
    return (m_type != NOEND) && m_finished;
}

bool Animation::deletable()
{
    return (m_type == ENDED) && m_finished;
}

void Animation::set_rect(Rect &pos)
{
    pos.h = m_images[m_curr]->h();
    pos.w = m_images[m_curr]->w();
}

void Animation::set_phase(int p)
{
    m_phase = p;
}
