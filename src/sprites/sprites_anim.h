#ifndef SPRITES_ANIM_H_INCLUDED
#define SPRITES_ANIM_H_INCLUDED

#include "sprites.h"
#include "../video/anim.h"

class Sprite_anim : public Sprite {
    private:
        Anim * m_anim;   /* gestionnaire d'animations */

    public:
        /**
         * Constructeur pour des images
         * Chemin donné à partir de /pic/
         */
        Sprite_anim(std::string anim_name, anim_type type, screen_level lvl);

        /**
         * Constructeur pour du texte
         */
        Sprite_anim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl);

        /**
         * Destructeur
         */
        ~Sprite_anim();

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
         *  @brief Change le texte de l'animation.
         */
        void change_text_to(std::string text, int begin_size, int end_size, int nb_pic);
};

#endif // SPRITES_ANIM_H_INCLUDED
