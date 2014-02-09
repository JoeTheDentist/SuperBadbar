/**
 * 	@file Sprite.h
 * 	@brief Header de la classe Sprite
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _SPRITES_
#define _SPRITES_

#include "actors/Actor.h"
#include "video/Surface.h"

class Surface;

enum screen_level
{
    BACKGROUND, MIDDLEGROUND, FOREGROUND, DASHGROUND /* le dernier existe pas en anglais, c'est une blague !*/
};

/**
 * 	@class Sprite
 * 	@brief Entites 2D afichables
 */
class Sprite
{
protected:
    Rect m_pos; 		    /* position du sprite et sa taille, pointe sur le Rect de son acteur */
    unsigned int m_phase;	/* phase pour alterner les images lors du déplacememnt */
    screen_level m_lvl;     /* niveau du plan d'affichage */
    bool m_to_delete;       /* si le sprite est �  détruire, ce booléen est mis �  jour par son acteur */
    bool m_no_pic;          /* si on doit afficher l'image ce tour ci */
    bool m_center;          /* si l'image doit être centrée sur la position */

public:
    /**
     *	@brief Constructeur
     */
    Sprite();

    /**
     *	@brief Destructeur
     */
    virtual ~Sprite();

    /**
     *	@brief Accesseur
     *	@return Un pointeur vers l'image actuelle du sprite
     */
    virtual Surface * curr_pic() = 0;

    /**
     *	@brief Change l'image �  venir
     */
    virtual void next_pic() = 0;

    /**
     *	@brief accesseur sur la position
     */
    Rect * pos();

    /**
     *  @brief Synchronise la position le l'acteur avec la position du sprite
     *  Attention, c'est aux curr_pic de bien mettre �  jour les dimensions de l'image.
     */
    void set_pos (Rect pos);

    /**
     *	@brief Change l'état, pour un joueur. Uniquement pour les anim_table.
     */
    virtual void change_anim (int s, Direction dir, bool fire = false, bool phase_rand = false);

    /**
     *  @brief Change le texte de l'animation. Uniquement pour les anims simples
     */
    virtual void change_text_to (std::string text, int begin_size, int end_size, int nb_pic);

    virtual int h()
    {
        return this->curr_pic()->h();
    }
    virtual int w()
    {
        return this->curr_pic()->w();
    }

    /**
     *	@brief Accesseur
     *	@return La phase du sprite
     */
    unsigned int phase() const;

    /**
     *  @brief Mutateur
     */
    void set_to_delete();

    /**
     *	@brief Accesseur
     *	@return Si on doit détruire le sprite
     */
    bool to_delete() const;

    /**
     *  @brief désactive l'affichage
     */
    void no_pic();

    /**
     *  @brief Remet l'affichage
     */
    void set_pic();

    /**
     *  @brief Mets l'image de départ aléatoirement, uniquement pour anim
     */
    virtual void rand_pic();

    /**
     *  @brief Accesseur, si l'image doit être centrée ou non
     */
    bool center();
};

#endif
