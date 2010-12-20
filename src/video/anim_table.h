/**
 * 	@file anim_manager.h
 * 	@brief Header de la classe Anim_table
 *
 * 	@author Guillaume BÃ©rard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef ANIM_TABLE_H_INCLUDED
#define ANIM_TABLE_H_INCLUDED

#include <SDL/SDL.h>
#include <string>

#include "animation.h"
#include "../sprites/sprites.h"
#include "../util/debug.h"

#define PICS_EXT ".bmp"


/**
 * 	@class Anim_table
 * 	@brief Automatise l'utilisation des animations
 */
class Anim_table
{
    private:
        char m_nb_states;           /* nombre d'etats de l'animation */
        state m_last_state;         /* dernier etat affiche, pour les changements d'animation */
        Animation * m_curr_anim;    /* pointeur sur l'animation courante */
        Animation *** m_anim;       /* tableau de pointeur vers les animations ; etat et gauche/droite */

    public:
        /**
         * @brief Constructeur intelligent, savant charger toutes les images propres au nom donné.
         *
         * A partir de la chaine de caractere : lien de l'image sans l'extension ni etat/dir, il sait
         * charger toutes les bonnes images... Check des fichier peut-être un peu longs.
         *
         * @param string donnant l'adresse du paquet d'image a charger
         */
        Anim_table(std::string anim_name);

        /**
         * @brief Destructeur, liberation du tableau des animations.
         */
        ~Anim_table();

        /**
         * @brief change l'animation courrante.
         */
        void change_anim(state s, horizontal dir);

        /**
         * @brief Accesseur a l'image courante de l'animation, l'image a afficher.
         */
        SDL_Surface * curr_pic();

        /**
         * @brief Permet de set hauteur et largeur d'un Rect par rapport a l'image courante.
         */
        void setRect(Rect & pos);
};

/**
 * Fonction permettant de savoir si un fichier existe ou non.
 * /!\ Il ne prend pas en compte la case. /!\
 * Avantage, ne depend pas du fait qu'on ait des permissions ou non sur le fichier.
 *
 * Code de DPAK, http://www.techbytes.ca/techbyte103.html.
 */
bool FileExists(std::string strFilename);


#endif // ANIM_MANAGER_H_INCLUDED
