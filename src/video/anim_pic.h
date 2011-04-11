/**
 * 	@file anim_pic.h
 * 	@brief Header de la classe Animation
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef ANIM_PIC_H_INCLUDED
#define ANIM_PIC_H_INCLUDED

#include <string>
#include "../util/globals.h"
#include "../video/animation.h"

#define ANIMATION_SPEED 3   /* Nombres de cycles entre deux images de l'animation (temps = TIME_LOOP * ANIMATION_SPEED) */

class Surface;
class Animation;

/**
 * 	@class Animation
 * 	@brief Classe animation, répresentant une succession d'images
 */
class Anim_pic: public Animation {
private:
    Surface ** m_images;

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
    Anim_pic(std::string * s, int size, anim_type type);

    /*!
	* @brief Destructeur
	*/
    ~Anim_pic();

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

    /*!
    * @brief si on peut supprimer l'animation.
    *
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

#endif // ANIMATION_H_INCLUDED
