/**
 * 	@file anim_manager.cpp
 * 	@brief Implémentation de la classe Anim_table
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <sys/stat.h>
#include <string>

#include "anim_table.h"

Anim_table::Anim_table(std::string anim_name) {
    char state = '0', dir = '0', num_img = '0';

    if ( !FileExists(anim_name+"_"+state+"_"+dir+"_"+num_img+PICS_EXT) ) {
        /* si aucun fichier de ce nom n'existe */
        PRINT_DEBUG(1, "Fichier inexistant %s", (anim_name+"_"+state+"_"+dir+"_"+num_img+PICS_EXT).c_str());
    }

    /* calcul du nombre d'etat */
    m_nb_states = 0;
    while ( FileExists(anim_name+"_"+state+"_"+dir+"_"+num_img+PICS_EXT) ) {
        state++;
    }
    m_nb_states = state-'0'+1;

    /* --> ici si m_nb_state = 1 on peut dire que c'est juste une animation => force = 1 ? */

    /* allocation du tableau d'animation */
    m_anim = new Animation**[m_nb_states];
    for (char i=0;i<m_nb_states;i++) {
        m_anim[i] = new Animation*[2];
    }

    /* creation des animations */
    for (char i='0';i<'0'+m_nb_states;i++) {
        for (char j='0';j<'0'+2;j++) {
            /* calcul du nombre d'images */
            char k;
            for (k='0'; FileExists(anim_name+"_"+i+"_"+j+"_"+k+PICS_EXT); k++) {}
            std::string * link;
            link = new std::string[k-'0'];

            for (k='0'; FileExists(anim_name+"_"+i+"_"+j+"_"+k+PICS_EXT); k++) {
                link[k-'0'] = anim_name+"_"+i+"_"+j+"_"+k+PICS_EXT;
            }

            /* creation de l'animation */
            m_anim[i-'0'][j-'0'] = new Animation(link,k-'0',false);
			delete[] link;
        }
    }

    m_curr_anim = m_anim[0][0];
}


Anim_table::~Anim_table() {
    for (int i=0;i<m_nb_states;i++) {
        delete m_anim[i][0];
        delete m_anim[i][1];
        delete[] m_anim[i];
    }
    delete[] m_anim;
}

void Anim_table::change_anim(state s, horizontal dir) {
    if ( m_curr_anim->interruptable() ) {
        m_curr_anim = m_anim[s][dir];
    }
}

SDL_Surface * Anim_table::curr_pic() {
    return m_curr_anim->curr_pic();
}

void Anim_table::setRect(Rect &pos)
{
    m_curr_anim->setRect(pos);
}




bool FileExists(std::string strFilename) {
  struct stat stFileInfo;
  bool blnReturn;
  int intStat;

  // Attempt to get the file attributes
  intStat = stat(strFilename.c_str(),&stFileInfo);
  if(intStat == 0) {
    // We were able to get the file attributes
    // so the file obviously exists.
    blnReturn = true;
  } else {
    // We were not able to get the file attributes.
    // This may mean that we don't have permission to
    // access the folder which contains this file. If you
    // need to do that level of checking, lookup the
    // return values of stat which will give you
    // more details on why stat failed.
    blnReturn = false;
  }

  return(blnReturn);
}
