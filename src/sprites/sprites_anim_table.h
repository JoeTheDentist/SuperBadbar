#ifndef SPRITES_ANIM_TABLE_H_INCLUDED
#define SPRITES_ANIM_TABLE_H_INCLUDED

#include "sprites.h"
#include "../video/anim_table.h"

class Sprite_anim_table : public Sprite {
    private:
        Anim_table * m_animt;   /* gestionnaire d'animations */

    public:
        /**
         * Constructeur
         */
        Sprite_anim_table(std::string anim_name, screen_level lvl);

        /**
         * Destructeur
         */
        ~Sprite_anim_table();

        /**
         * Image � afficher
         *  +maj de m_pos
         */
        Surface * curr_pic();

        /**
         * Passe � l'image suivante
         */
        void next_pic();

        /**
         *	@brief Change l'�tat, pour un joueur.
         */
        void change_anim(state_player s, direction dir, bool fire=false ,bool phase_rand=false);

        /**
         *	@brief Change l'�tat pour un monstre.
         */
        void change_anim(state_m s, direction dir, bool fire=false ,bool phase_rand=false);

        /**
         *  @brief Hauteur
         *  @return Hauteur
         */
        int h();

        /**
         *  @brief Largeur
         *  @return Largeur
         */
        int w();
};

#endif // SPRITES_ANIM_TABLE_H_INCLUDED