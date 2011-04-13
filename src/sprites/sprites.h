/**
 * 	@file sprites.h
 * 	@brief Header de la classe Sprite
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _SPRITES_
#define _SPRITES_

#include "../actors/actor.h"
#include "../video/surface.h"

class Surface;

enum screen_level {
    BACKGROUND, MIDDLEGROUND, FOREGROUND, DASHGROUND /* le dernier existe pas en anglais, c'est une blague !*/
};

/**
 * 	@class Sprite
 * 	@brief Entités 2D afichables
 */
class Sprite {
    protected:
        Rect * m_pos; 		    /* position du sprite et sa taille, pointe sur le Rect de son acteur */
        unsigned int m_phase;	/* phase pour alterner les images lors du déplacememnt */
        screen_level m_lvl;     /* niveau du plan d'affichage */
        bool m_to_delete;       /* si le sprite est à détruire, ce booléen est mis à jour par son acteur */

    public:
        /**
         *	@brief Constructeur
         */
        Sprite();

        /**
         *	@brief Destructeur
         */
        ~Sprite();

        /**
         *  @brief Relation d'ordre pour le sort
         */
        bool operator<(const Sprite &s) const;

        /**
         *	@brief Accesseur
         *	@return Un pointeur vers l'image actuelle du sprite
         */
        virtual Surface * curr_pic()=0;

        /**
         *	@brief Change l'image à venir
         */
        virtual void next_pic()=0;

        /**
         *	@brief accesseur sur la position
         */
        Rect * pos();

        /**
         *  @brief Synchronise la position le l'acteur avec la position du sprite
         *  Attention, c'est aux curr_pic de bien mettre à jour les dimensions de l'image.
         */
        void synchro(Rect * pos);

        /**
         *	@brief Change l'état, pour un joueur. Uniquement pour les anim_table.
         */
        virtual void change_anim(state_player s, direction dir, bool fire=false, bool phase_rand=false);

        /**
         *	@brief Change l'état pour un monstre. Uniquement pour les anim_table.
         */
        virtual void change_anim(state_m s, direction dir, bool fire=false, bool phase_rand=false);

        /**
         *  @brief Change le texte de l'animation. Uniquement pour les anims simples
         */
        virtual void change_text_to(std::string text, int begin_size, int end_size, int nb_pic);

        /**
         *	@brief Accesseur
         *	@return La phase du sprite
         */
        unsigned int phase() const;

        /**
         *  @brief Mutateur
         */
        void set_to_delete();

        /**
         *	@brief Accesseur
         *	@return Si on doit détruire le sprite
         */
        bool to_delete() const;
};

#endif
