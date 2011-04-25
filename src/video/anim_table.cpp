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
//    char state = '0', dir = '0', num_img = '0';
//    char k1;
//    char k2;
//
//    /* calcul du nombre d'etat */
//    m_nb_states = 0;
//    while ( FileExists(anim_name+"_"+state+"_"+dir+"_"+num_img+PICS_EXT) ) {
//        state++;
//    }
//    m_nb_states = state-'0'+1;
//
//    /* allocation du tableau d'animation 2x pour les états de tir */
//    m_anim = new Anim_pic**[2*m_nb_states];
//    for (int i=0;i<m_nb_states;i++) {
//        m_anim[i] = new Anim_pic*[2];
//    }
//
//    /* creation des animations */
//    for (char i='0';i<'0'+m_nb_states;i++) {
//        for (char j='0';j<'0'+2;j++) {
//            /* calcul du nombre d'images */
//            for (k1='0'; FileExists(anim_name+"_"+i+"_"+j+"_"+k1+"_0"+PICS_EXT); k1++) {}
//            for (k2='0'; FileExists(anim_name+"_"+i+"_"+j+"_"+k2+"_1"+PICS_EXT); k2++) {}
//
//            /* récurépration des noms */
//            std::string * link1;
//            std::string * link2;
//            link1 = new std::string[k1-'0'];
//            link2 = new std::string[k2-'0'];
//            for (k1='0'; FileExists(anim_name+"_"+i+"_"+j+"_"+k1+"_0"+PICS_EXT); k1++) {
//                link1[k1-'0'] = anim_name+"_"+i+"_"+j+"_"+k1+"_0"+PICS_EXT;
//            }
//            for (k2='0'; FileExists(anim_name+"_"+i+"_"+j+"_"+k2+"_1"+PICS_EXT); k2++) {
//                link1[k2-'0'] = anim_name+"_"+i+"_"+j+"_"+k2+"_1"+PICS_EXT;
//            }
//
//            /* creation de l'animation */
//            m_anim[i-'0'][j-'0'] = new Anim_pic(link1,k1-'0',CYCLE);
//            m_anim[i-'0'+m_nb_states][j-'0'] = new Anim_pic(link2,k2-'0',ENDED);
//			delete[] link1;
//			delete[] link2;
//        }
//    }
//
//    m_nb_states *= 2;
//    m_curr_anim = m_anim[0][0];
}

void Anim_table::init_nfire(std::string anim_name)
{
    char state = '0', dir = '0', num_img = '0';

    /* calcul du nombre d'etat */
    m_nb_states = 0;
    while ( FileExists(anim_name+"_"+state+"_"+dir+"_"+num_img+PICS_EXT) ) {
        state++;
    }
    m_nb_states = state-'0';

    /* allocation du tableau d'animation */
    m_anim = new Anim_pic**[m_nb_states];
    for (int i=0;i<m_nb_states;i++) {
        m_anim[i] = new Anim_pic*[2];
    }

    /* creation des animations */
    for (char i='0';i<'0'+m_nb_states;i++) {
        for (char j='0';j<'0'+2;j++) {
            std::string link = anim_name+"_"+i+"_"+j;
            /* creation de l'animation */
            m_anim[i-'0'][j-'0'] = new Anim_pic(link,CYCLE);
        }
    }

    m_curr_anim = m_anim[0][0];
}

void Anim_table::change_anim(int s, direction dir, bool fire, bool phase_rand) {
    if ( fire ) {
        s += m_nb_states/2;
    }

    if ( s != m_last_state || dir != m_last_dir ) {
        if ( m_curr_anim->interruptable() ) {
            m_curr_anim = m_anim[s][dir];
            if ( phase_rand ) {
                m_curr_anim->set_img( rand()%3 );
            }
        }
        m_last_state = s;
        m_last_dir = dir;
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
