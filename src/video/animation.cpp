#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "animation.h"

Animation::Animation() {
    m_images = NULL;
    m_size = 0;
    m_curr = 0;
    m_phase = 0;
}

Animation::Animation(std::string * s, int size, bool force) {
    m_images = new SDL_Surface*[size];
    m_size = size;
    m_curr = 0;
    m_phase = 0;

    for (int i=0;i<size;i++) {
        m_images[i] = SDL_LoadBMP((s[i]).c_str());
        SDL_SetColorKey(m_images[i], SDL_SRCCOLORKEY, SDL_MapRGB(m_images[i]->format, 0, 0, 255));
    }

    if ( force ) {
        m_finished = false;
    } else {
        m_finished = true;
    }
}

Animation::~Animation() {
    for (int i=0;i<m_size;i++) {
        SDL_FreeSurface(m_images[i]);
    }
    delete[] m_images;
}

SDL_Surface * Animation::curr_pic() {
    SDL_Surface * image = m_images[m_curr];
    m_phase++;
    m_phase%=ANIMATION_SPEED;

    if ( m_phase == 0 ) {
        if ( m_force && m_finished ) {  /* si on a fini en forcé, on garde toujours la derniere image */
            m_curr = m_size-1;
        } else {                        /* sinon on affiche les images cycliquement */
            m_curr++;
            m_curr%=m_size;
        }

        if ( m_force && ( m_curr == 0 ) ) { /* une fois qu'on a fini une animation en forcé, on a fini */
            m_finished = true;
        }
    }

    return image;
}

unsigned int Animation::h(int i) {
    return (unsigned int)m_images[i]->h;
}

unsigned int Animation::w(int i) {
    return (unsigned int)m_images[i]->w;
}
