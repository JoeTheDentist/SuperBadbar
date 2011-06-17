/**
 * 	@file anim_manager.cpp
 * 	@brief Implémentation de la classe Anim_table
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#include <iostream>
#include <stdint.h>
#include <string>
#include "../video/surface.h"
#include <stdlib.h>
#include "anim_table.h"

Anim_table::Anim_table(std::string anim_name) {
    m_last_state = 0;
    m_last_dir = LEFT;
    m_fire = false;
    m_last_fire = false;

    /* On détermine si il y a un état en plus ou non (animation de tir) */
    if ( FileExists(anim_name+"_0_0_0"+PICS_EXT) ) {
        m_fire = false;
    } else if ( FileExists(anim_name+"_0_0_0_0"+PICS_EXT) ) {
        m_fire = true;
    } else {
        /* si aucun fichier de ce nom n'existe */
        PRINT_DEBUG(1, "Fichier inexistant %s", (anim_name+"_0_0_0"+PICS_EXT).c_str());
    }

    /* on choisit la fonction d'initialisation en fonction du fait si il y a une animation de tir */
    if ( m_fire ) {
        init_fire(anim_name);
    } else {
        init_nfire(anim_name);
    }
}


Anim_table::~Anim_table() {
    for (int i=0;i<m_nb_states;i++) {
        delete m_anim[i][0];
        delete m_anim[i][1];
        delete[] m_anim[i];
    }
    delete[] m_anim;
}

void Anim_table::init_fire(std::string anim_name)
{
    int state = 0;

    /* calcul du nombre d'etat */
    m_nb_states = 0;

    while ( FileExists(anim_name+"_"+to_string(state)+"_0_0_0"+PICS_EXT) ) {
        state++;
    }
    m_nb_states = state;

    /* allocation du tableau d'animation */
    m_anim = new Anim_pic**[2*m_nb_states];
    for (int i=0;i<2*m_nb_states;i++) {
        m_anim[i] = new Anim_pic*[2];
    }

    /* creation des animations */
    for (int i=0 ; i<m_nb_states ; i++) {
        for (int j=0 ; j<2 ; j++) {
            for (int k=0 ; k<2 ; k++) {
                std::string link = anim_name+"_"+to_string(i)+"_"+to_string(j)+"_"+to_string(k);
                /* creation de l'animation */
                m_anim[i+k*m_nb_states][j] = new Anim_pic(link,CYCLE);
            }
        }
    }

    m_curr_anim = m_anim[0][0];
}

void Anim_table::init_nfire(std::string anim_name)
{
    int state = 0;

    /* calcul du nombre d'etat */
    m_nb_states = 0;

    while ( FileExists(anim_name+"_"+to_string(state)+"_0_0"+PICS_EXT) ) {
        state++;
    }
    m_nb_states = state;

    /* allocation du tableau d'animation */
    m_anim = new Anim_pic**[m_nb_states];
    for (int i=0;i<m_nb_states;i++) {
        m_anim[i] = new Anim_pic*[2];
    }

    /* creation des animations */
    for (int i=0 ; i<m_nb_states ; i++) {
        for (int j=0 ; j<2 ; j++) {
            std::string link = anim_name+"_"+to_string(i)+"_"+to_string(j);
            /* creation de l'animation */
            m_anim[i][j] = new Anim_pic(link,CYCLE);
        }
    }

    m_curr_anim = m_anim[0][0];
}

void Anim_table::change_anim(int s, direction dir, bool fire, bool phase_rand)
{
    if ( s != m_last_state || dir != m_last_dir || fire != m_last_fire ) {
        if ( m_curr_anim->interruptable() ) {
            if ( fire ) {
                m_curr_anim = m_anim[s+m_nb_states][dir];
            } else {
                m_curr_anim = m_anim[s][dir];
            }
            if ( phase_rand ) {
                m_curr_anim->set_img( rand()%3 );
            }
        }
        m_last_state = s;
        m_last_dir = dir;
        m_last_fire = fire;
    }
}

Surface * Anim_table::curr_pic() {
    return m_curr_anim->curr_pic();
}

void Anim_table::next_pic() {
    m_curr_anim->next_pic();
}

void Anim_table::set_rect(Rect &pos)
{
    m_curr_anim->set_rect(pos);
}

void Anim_table::set_img(int i)
{
    m_curr_anim->set_img(i);
}
