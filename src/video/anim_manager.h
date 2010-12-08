#ifndef ANIM_MANAGER_H_INCLUDED
#define ANIM_MANAGER_H_INCLUDED

#include <SDL/SDL.h>
#include <string>

#include "animation.h"
#include "../sprites/sprites.h"
#include "../util/debug.h"

#define PICS_EXT ".bmp"

/*!
 * Classe ayant pour but d'automatiser l'utilisation des animations.
 */

class Anim_manager
{
    private:
        char m_nb_states;
        state m_last_state;
        Animation * m_curr_anim;
        Animation *** m_anim;    /* tableau de pointeur vers les animations ; etat et gauche/droite */

    public:
        /*!
         * Constructeur par defaut.
         */
        Anim_manager();

        /*!
         * @brief Constructeur intelligent, savant charger toutes les images propres au nom donn�.
         *
         * A partir de la chaine de caractere : lien de l'image sans l'extension ni etat/dir, il sait
         * charger toutes les bonnes images... Check des fichier peut-�tre un peu longs.
         */
        Anim_manager(std::string anim_name);

        /*!
         * @brief Destructeur, liberation du tableau des animations.
         */
        ~Anim_manager();

        /*!
         * @brief change l'animation courrante.
         */
        void change_anim(state s, horizontal dir);

        /*!
         * @brief Accesseur a l'image courante de l'animation, l'image a afficher.
         */
        SDL_Surface * curr_pic();

        /*!
         * @brief Permet de set hauteur et largeur d'un Rect par rapport a l'image courante.
         */
        void setRect(Rect & pos);
};

/*!
 * Fonction permettant de savoir si un fichier existe ou non.
 * /!\ Il ne prend pas en compte la case.
 * Avantage, ne depend pas du fait qu'on ait des permissions ou non sur le fichier.
 *
 * Code de DPAK, http://www.techbytes.ca/techbyte103.html.
 */
bool FileExists(std::string strFilename);


#endif // ANIM_MANAGER_H_INCLUDED