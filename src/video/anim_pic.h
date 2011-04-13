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
#include "../video/anim.h"

#define ANIMATION_SPEED 3   /* Nombres de cycles entre deux images de l'animation (temps = TIME_LOOP * ANIMATION_SPEED) */

class Surface;
class Anim;

/**
 * 	@class Anim
 * 	@brief Classe animation, répresentant une succession d'images
 */
class Anim_pic: public Anim {
private:
    Surface ** m_images;

public:

    /*!
	* @brief Constructeur
	*
	* Constructeur d'animation.
	* Impose de creer une animation avec une seule image...
	*
	* @param noms des images à charger, supporte : x0.png, x_0.png ou x.png
	*   , où x nom de l'anim et 0 un nombre. Si x.png : une seule image.
	*   Le chemin donné se fait à partir du dossier pic.
	* @param force si on doit attendre la terminaison
	*
	*/
    Anim_pic(std::string anim_name, anim_type type);

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
    * @brief passe à l'image suivante
    */
    void next_pic();

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
