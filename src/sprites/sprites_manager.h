#ifndef SPRITES_MANAGER_H_INCLUDED
#define SPRITES_MANAGER_H_INCLUDED

#include "sprites.h"
#include "../video/anim.h"
#include "../video/camera.h"

/**
 *  @class Sprites_manager
 *  @brief Classe manageant les sprites.
 *  ATTENTION la cr�ation et la destruction des sprites se fait ici et nul part ailleurs !
 */

class Sprites_manager {
    private:
        std::list<Sprite*> * m_sprites;    /* liste � trier, le tri ne se fait qu'� l'ajout : booleen to_sort=true */
        bool m_to_sort;

        /**
         *  @brief Ajoute du sprite dans la liste
         */
        void add(Sprite * s);
    public:
        /**
         * Constructeur
         */
        Sprites_manager();

        /**
         * Destructeur
         */
        ~Sprites_manager();

        /**
         * Abonne une table d'animation
         */
        Sprite * add_anim(std::string anim_name, anim_type type, screen_level lvl);

        /**
         * Pour un text anim�
         */
        Sprite * add_anim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl);

        /**
         * Abonne une animation
         */
        Sprite * add_table(std::string anim_name, screen_level lvl);

        /**
         * M�thode de mise � jour de la liste, tri (�ventuel) + next_pic pour tous les sprites !
         * Supprimer les �l�ments � supprimer (to_delete)
         */
        void update();

        /**
         * Vide la liste, sans la d�truire
         */
        void clear();

        /**
         *  @brief Affiche les images
         */
        void display_sprites(Camera * cam);
};

#endif // SPRITES_MANAGER_H_INCLUDED
