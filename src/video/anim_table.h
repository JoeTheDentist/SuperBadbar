/**
 * 	@file anim_manager.h
 * 	@brief Header de la classe Anim_table
 *
 * 	@author Guillaume Berard & Benoit Morel
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

#define PICS_EXT ".png"

class Surface;

/**
 * 	@class Anim_table
 * 	@brief Automatise l'utilisation des animations
 */
class Anim_table
{
    private:
        char m_nb_states;           /* nombre d'etats de l'animation */
        int m_last_state;           /* dernier etat affiche, pour les changements d'animation */
        Animation * m_curr_anim;    /* pointeur sur l'animation courante */
        Animation ***m_anim;        /* tableau de pointeur vers les animations ; etat et gauche/droite */
        bool m_fire;                /* si il y a un état de tir dans les animations */

        /**
         * @brief Construction de l'animation pour un monstre ayant un état de tir (2x plus d'images)
         */
        void init_fire(std::string anim_name);

        /**
         * @brief Construction de l'animation pour un monstre sans état de tir
         */
        void init_nfire(std::string anim_name);

    public:
        /**
         * @brief Constructeur intelligent, savant charger toutes les images propres au nom donné.
         *
         * A partir de la chaine de caractere : lien de l'image sans l'extension ni etat/dir, il sait
         * charger toutes les bonnes images... Check des fichier peut-être un peu longs.
         * /!\\ Les num des images doivent correspondrent à l'enum de l'état correspondant...
         *
         *  @param string donnant l'adresse du paquet d'image a charger
         */
        Anim_table(std::string anim_name);

        /**
         * @brief Destructeur, liberation du tableau des animations.
         */
        ~Anim_table();

        /**
         * @brief change l'animation courrante, en prenant en compte si l'animation est stoppable.
         */
        void change_anim(int s, direction dir);

        /**
         * @brief change l'animation courrante, si fire, affiche l'animation de tir.
         */
        void change_anim(int s, direction dir, bool fire);

        /**
         * @brief Accesseur a l'image courante de l'animation, l'image a afficher (à appeler une fois par cycle).
         */
        Surface * curr_pic();

        /**
         *  @brief Set hauteur et largeur en fonction de l'image courante
         *
         *  @param Rect a modifier
         */
        void set_rect(Rect &pos);
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
