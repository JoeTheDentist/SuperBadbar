/**
 * 	@file animation.cpp
 * 	@brief Implémentation de la classe Animation
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <stdint.h>

#include "AnimPic.h"
#include "../video/surface.h"


AnimPic::AnimPic(std::string anim_name, anim_type type) {
    std::string sup;
    if ( FileExists(PIC_R+anim_name+"_"+"0"+PICS_EXT) ) {
        sup = "_";
    } else if ( FileExists(PIC_R+anim_name+"0"+PICS_EXT) ) {
        sup = "";
    } else if ( FileExists(PIC_R+anim_name+PICS_EXT) ) {
        /* si on a juste une image avec le nom stipul� */
        m_images = new Surface*[1];
        m_size = 1;
        m_curr = 0;
        m_phase = 0;
        m_images[0] = new Surface(PIC_R+anim_name+PICS_EXT);

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
    char num[3];
    int size = 0;
    sprintf(num,"%d",size);
    for (size=0; FileExists(PIC_R+anim_name+sup+num+PICS_EXT); size++ ) {
        sprintf(num,"%d",size);
    }
    size -= 1;

    m_images = new Surface*[size];
    m_size = size;
    m_curr = 0;
    m_phase = 0;

    for (int i=0;i<size;i++) {
        sprintf(num,"%d",i);
        m_images[i] = new Surface(PIC_R+anim_name+sup+num+PICS_EXT);
    }

    m_type = type;

    if ( type == CYCLE ) {
        m_finished = true;
    } else {
        m_finished = false;
    }
}

AnimPic::~AnimPic() {
    for (int i=0;i<m_size;i++) {
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
        if ( m_type != CYCLE && m_finished ) {  /* si on a fini sans �tre en CYCLE, on garde la derni�re image */
            m_curr = m_size-1;
        } else {                        /* sinon on affiche les images cycliquement */
            m_curr++;
            m_curr%=m_size;
        }

        if ( m_type != CYCLE && ( m_curr == m_size-1 ) ) { /* une fois qu'on a fini une animation en forc�, on a fini */
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
