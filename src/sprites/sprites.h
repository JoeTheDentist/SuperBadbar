/**
 * 	@file sprites.h
 * 	@brief Header de la classe Sprite
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _SPRITES_
#define _SPRITES_

#define GRAVITE 7           /* Constante pour la décélération de saut */
#define DAMAGE_BOX_RATIO 5
#include "../items/weapons.h"


	/*!
	 *	@brief Etat, utile pour les animations, pour savoir quelle serie d'image afficher
	 *
	 *	Sert également à savoir ce que le sprite peut ou ne peut pas faire
	*/

#include "../video/anim_pic.h"
#include "../video/anim_table.h"
#include "../video/displayable.h"

/* /!\ Les enums direction et vertical sont dans weapon... */

class Static_data;
class Keyboard;
class Camera;
class Anim_table;
class Collisions_manager;
class Surface;

/**
 * 	@class Sprite
 * 	@brief Entités 2D mobiles et afichables
 */
class Sprite: public Displayable {
protected:
	Rect m_pos; 		        /* position du sprite et sa taille */
	Rect m_speed;		        /* vitesse du sprite */
	direction m_dir;    /* direction directione */
	Anim_table * m_animt;     /* gestionnaire d'animations */
	uint32_t m_phase;		    /* phase pour alterner les images lors du déplacememnt */
public:
	/*!
	 *	@brief Constructeur
	*/
	Sprite();

	/*!
	 *	@brief Destructeur
	*/
	virtual ~Sprite();

	/*!
	 *	@brief Accesseur
	 *	@return Un pointeur vers l'image actuelle du sprite
	*/
    virtual Surface *current_picture() const;

	/*!
	 *	@brief Met à jour la position du sprite
	 *	@param static_data Données du jeu
	 *	@param collisions_manager Gestionnaire de collisions
	*/
    void update_pos();

	/*!
	 *	@brief Accesseur
	 *	@return La position du sprite
	*/
	virtual Rect position() const;


	Rect damage_box() const;

	/*!
	 *	@brief Accesseur
	 *	@return L'abscisse de la position du sprite
	*/
	uint32_t position_x() const;

	/*!
	 *	@brief Accesseur
	 *	@return L'ordonnée de la position du sprite
	*/
	uint32_t position_y() const;

	/*!
	 *	@brief Accesseur
	 *	@return La phase du sprite
	*/
	uint32_t phase() const;

	/*!
	 *	@brief Accesseur
	 *	@return La direction directione du sprite
	 *
	 *	-1 pour gauche, 0 pour milieu, 1 pour droite
	*/
	int direction_h() const; /* retourne la direction directione du sprite (-1 pour gauche, 0 pour middle, 1 pour droite*/

	direction dir() const;
};







#endif
