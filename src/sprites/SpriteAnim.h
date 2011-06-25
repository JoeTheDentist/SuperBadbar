#ifndef SPRITES_ANIM_H_INCLUDED
#define SPRITES_ANIM_H_INCLUDED

#include "Sprite.h"
#include "../video/anim.h"

class SpriteAnim : public Sprite {
    private:
        Anim * m_anim;   /* gestionnaire d'animations */

    public:
        /**
         * Constructeur pour des images
         * Chemin donné à partir de /pic/
         */
        SpriteAnim(std::string anim_name, anim_type type, screen_level lvl, bool center=false);

        /**
         * Constructeur pour du texte
         */
        SpriteAnim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl);

        /**
         * Destructeur
         */
        ~SpriteAnim();

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

        /**
         *  @brief Mets l'image de départ aléatoirement
         */
        void rand_pic();
};

#endif // SPRITES_ANIM_H_INCLUDED
