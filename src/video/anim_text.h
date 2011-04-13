#ifndef ANIM_TEXT_H_INCLUDED
#define ANIM_TEXT_H_INCLUDED

#include "../video/anim.h"
#include "../video/surface_text.h"

class Anim;


class Anim_text: public Anim {
    private:
        std::string m_text;
        int m_begin_size;
        int m_end_size;
        int m_curr_num;
        int m_nb_pic;
        Surface_text * m_last_surf;

    public:
        /*!
        * @brief Constructeur
        *
        * Rq : Pour avoir un cardre fixe, on prend le max de la taille et la chaque surface a cette taille
        *
        * @param text : texte à afficher
        * @param begin_size : taille de début
        * @param end_size : taille de fin
        * @param nb_pic : nombre d'images à jouer
        *
        */
        Anim_text(std::string text, int begin_size, int end_size, int nb_pic);

        /*!
        * @brief Destructeur
        */
        ~Anim_text();

        /*!
        * @brief Image a afficher.
        * @return l'image de l'animation a afficher.
        */
        Surface * curr_pic();

        /*!
        * @brief Passe à l'image suivante
        */
        void next_pic();

        /*!
        * @brief si on peut interrompre l'animation.
        * @return booleen, true si on peut l'interrompre.
        */
        bool interruptable();

        /*!
        * @brief si on peut supprimer l'animation.
        * @return booleen, true si on peut la suppr.
        */
        bool deletable();

        /**
         *  @brief Set hauteur et largeur en fonction de l'image courante
         *
         *  @param pos Rect à modifier
         */
        void set_rect(Rect &pos);

        /**
         * @brief Set phase
         * @param Nouvelle phase
         */
        void set_img(int p);
};

#endif // ANIM_TEXT_H_INCLUDED
