#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <SDL/SDL.h>
#define ANIMATION_SPEED 6   /* Nombres de cycles entre deux images de l'animation (temps = TIME_LOOP * ANIMATION_SPEED) */

class Animation {
private:
    SDL_Surface ** m_images;
    int m_curr;                 /* image courante */
    int m_size;                 /* nombre d'images stockees */
    bool m_force;               /* attente de la terminaison de l'animation */
    bool m_finished;            /* si l'animation peut être interrompue */
    int m_phase;                /* nombre de cycle depuis lequel l'animation a ete cree */

public:
    Animation();

    /*!
	* @brief Constructeur
	*
	* Constructeur d'animation.
	* Impose de creer une animation avec une seule image...
	*
	* @param s tableau des chemins de images a charger
	* @param size nombre d'image de l'animation
	* @param force si on doit attendre la terminaison
	*
	*/
    Animation(std::string * s, int size, bool force);

    /*!
	* @brief Destructeur
	*/
    ~Animation();

    /*!
    * @brief Image a afficher.
    *
    * @return l'image de l'animation a afficher.
    */
    SDL_Surface * curr_pic();
    /*!
    * @brief si on peut interrompre l'animation.
    *
    * @return booleen, true si on peut l'interrompre.
    */
    bool interruptable();


    unsigned int h(int i);

    unsigned int w(int i);

};

#endif // ANIMATION_H_INCLUDED
