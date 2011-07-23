/**
 * 	@file animation.cpp
 * 	@brief Implémentation de la classe Animation
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <stdint.h>

#include "AnimPic.h"
#include "../video/Surface.h"


AnimPic::AnimPic(std::string anim_name, anim_type type)
{
    std::string sup;
    if ( FileExists(anim_name+"_"+"0"+PICS_EXT) ) {
        sup = "_";
    } else if ( FileExists(anim_name+"0"+PICS_EXT) ) {
        sup = "";
    } else if ( FileExists(anim_name+PICS_EXT) ) {
        /* si on a juste une image avec le nom stipule */
        m_images = new Surface*[1];
        m_size = 1;
        m_curr = 0;
        m_phase = 0;
        m_images[0] = new Surface(anim_name+PICS_EXT);

        m_type = type;
        if ( type == CYCLE ) {
            m_finished = true;
        } else {
            m_finished = false;
        }

        return;
    } else {
        PRINT_DEBUG(1, "Fichier inexistant %s, crash iminent !!!", anim_name.c_str() )
    }

    std::string test = anim_name;

    /* calcul du nombre d'images */
    int size = 0;
    for (size=0; FileExists(anim_name+sup+to_string(size)+PICS_EXT); size++ ) {}

    m_images = new Surface*[size];
    m_size = size;
    m_curr = 0;
    m_phase = 0;

    for (int i = 0; i < size; i++) {
        m_images[i] = new Surface(anim_name + sup + to_string(i) + PICS_EXT);
    }

    m_type = type;

    if ( type == CYCLE ) {
        m_finished = true;
    } else {
        m_finished = false;
    }
}

AnimPic::~AnimPic()
{
    for (int i = 0; i < m_size; i++) {
        delete m_images[i];
    }
    delete[] m_images;
}

Surface * AnimPic::curr_pic()
{
    return m_images[m_curr];
}

void AnimPic::next_pic()
{
    m_phase++;
    m_phase%=ANIMATION_SPEED;

    if ( m_phase == 0 ) {
        if ( m_type != CYCLE && m_finished ) {  /* si on a fini sans etre en CYCLE, on garde la derniere image */
            m_curr = m_size-1;
        } else {                        /* sinon on affiche les images cycliquement */
            m_curr++;
            m_curr%=m_size;
        }

        if ( m_type != CYCLE && ( m_curr == m_size-1 ) ) { /* une fois qu'on a fini une animation en force, on a fini */
            m_finished = true;
        }
    }
}

bool AnimPic::interruptable()
{
    return (m_type != NOEND) && m_finished;
}

bool AnimPic::deletable()
{
    return (m_type == ENDED) && m_finished;
}

void AnimPic::set_rect(Rect &pos)
{
    pos.h = m_images[m_curr]->h();
    pos.w = m_images[m_curr]->w();
}

void AnimPic::set_img(int p)
{
    m_curr = p%m_size;
}
