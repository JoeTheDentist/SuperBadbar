/**
 * 	@file AnimPic.h
 * 	@brief Header de la classe Animation
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef ANIM_PIC_H_INCLUDED
#define ANIM_PIC_H_INCLUDED

#include <string>

#include <util/globals.h>
#include <video/Anim.h>

#define ANIMATION_SPEED 3   /* Nombres de cycles entre deux images de l'animation (temps = TIME_LOOP * ANIMATION_SPEED) */

class Surface;
class Anim;

/**
 * 	@class Anim
 * 	@brief Classe animation, r√©presentant une succession d'images
 */
class AnimPic: public Anim {
private:
    Surface ** m_images;

public:

    /**
	* @brief Constructeur
	*
	* Constructeur d'animation.
	* Impose de creer une animation avec une seule image...
	*
	* @param noms des images √  charger, supporte : x0.png, x_0.png ou x.png
	*   , o√π x nom de l'anim et 0 un nombre. Si x.png : une seule image.
	*   Le chemin donn√© se fait √  partir de l'exe
	* @param force si on doit attendre la terminaison
	*
	*/
    AnimPic(std::string anim_name, anim_type type);

    /**
	* @brief Destructeur
	*/
    virtual ~AnimPic();

    /**
    * @brief Image a afficher.
    *
    * @return l'image de l'animation a afficher.
    */
    Surface * curr_pic();

    /**
    * @brief passe √  l'image suivante
    */
    void next_pic();

    /**
    * @brief si on peut interrompre l'animation.
    *
    * @return booleen, true si on peut l'interrompre.
    */
    bool interruptable();

    /**
    * @brief si on peut supprimer l'animation.
    *
    * @return booleen, true si on peut la suppr.
    */
    bool deletable();

    /**
     *  @brief Set hauteur et largeur en fonction de l'image courante
     *
     *  @param pos Rect √  modifier
     */
    void set_rect(Rect &pos);

    /**
     * @brief Set phase
     * @param Nouvelle phase
     */
    void set_img(int p);
};

#endif // ANIMATION_H_INCLUDED
