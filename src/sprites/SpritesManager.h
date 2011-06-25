#ifndef SPRITES_MANAGER_H_INCLUDED
#define SPRITES_MANAGER_H_INCLUDED

#include "Sprite.h"
#include "../video/anim.h"
#include "../video/Camera.h"

/**
 *  @class SpritesManager
 *  @brief Classe manageant les sprites.
 *  ATTENTION la création et la destruction des sprites se fait ici et nul part ailleurs !
 */

class SpritesManager {
    private:
        std::list<Sprite*> * m_sprites;    /* liste à trier, le tri ne se fait qu'à l'ajout : booleen to_sort=true */

        /**
         *  @brief Ajoute du sprite dans la liste
         */
        void add(Sprite * s, bool back=false);
    public:
        /**
         * Constructeur
         */
        SpritesManager();

        /**
         * Destructeur
         */
        ~SpritesManager();

        /**
         * Abonne une table d'animation
         */
        Sprite * add_anim(std::string anim_name, anim_type type, screen_level lvl, bool center=false);

        /**
         * Pour un text animé
         */
        Sprite * add_anim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl);

        /**
         * Abonne une animation
         */
        Sprite * add_table(std::string anim_name, screen_level lvl);

        /**
         * Méthode de mise à jour de la liste, next_pic pour tous les sprites !
         */
        void update();

        /**
         * Méthode de suppression des éléments.
         */
        void delete_dead_sprites();

        /**
         * Vide la liste, sans la détruire
         */
        void clear();

        /**
         *  @brief Affiche les images
         */
        void display_sprites(Camera * cam);
};

#endif // SPRITES_MANAGER_H_INCLUDED
