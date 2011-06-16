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
         * Image à afficher
         *  +maj de m_pos
         */
        Surface * curr_pic();

        /**
         * Passe à l'image suivante
         */
        void next_pic();

        /**
         *	@brief Change l'état
         */
        void change_anim(int s, direction dir, bool fire=false ,bool phase_rand=false);

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

        void rand_pic();
};

#endif // SPRITES_ANIM_TABLE_H_INCLUDED
