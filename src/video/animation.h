/**
 * 	@file animation.h
 * 	@brief Header de la classe Animation
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <SDL/SDL.h>

#include "../util/globals.h"

#define ANIMATION_SPEED 3   /* Nombres de cycles entre deux images de l'animation (temps = TIME_LOOP * ANIMATION_SPEED) */

class Surface;

/**
 * 	@class Animation
 * 	@brief
 */
class Animation {
private:
    Surface ** m_images;
    int m_curr;                 /* image courante */
    int m_size;                 /* nombre d'images stockees */
    bool m_force;               /* attente de la terminaison de l'animation */
    bool m_finished;            /* si l'animation peut etre interrompue */
    int m_phase;                /* nombre de cycle depuis lequel l'animation a ete cree */

public:

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
    Surface * curr_pic();
    /*!
    * @brief si on peut interrompre l'animation.
    *
    * @return booleen, true si on peut l'interrompre.
    */
    bool interruptable();


    /**
     *  @brief Set hauteur et largeur en fonction de l'image courante
     *
     *  @param pos Rect à modifier
     */
    void setRect(Rect &pos);
};

#endif // ANIMATION_H_INCLUDED
