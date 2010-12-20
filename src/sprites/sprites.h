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

#include "SDL/SDL.h"
#include "../items/weapons.h"

	/*!
	 *	@enum state
	 *	@brief Etat, utile pour les animations, pour savoir quelle serie d'image afficher
	 *
	 *	Sert également à savoir ce que le sprite peut ou ne peut pas faire
	*/
enum state {
    STATIC, WALK, JUMP
};

#include "../video/animation.h"
#include "../video/anim_table.h"

/* /!\ Les enums horizontal et vertical sont dans weapon... */

class Static_data;
class Sound_manager;
class Keyboard;
class Camera;
class Anim_table;
class Collisions_manager;
class Pictures_manager;

/**
 * 	@class Sprite
 * 	@brief Entités 2D mobiles et afichables
 */
class Sprite{
protected:
	static Pictures_manager *m_pictures_manager;
	Rect m_pos; 		        /* position du sprite et sa taille */
	Rect m_speed;		        /* vitesse du sprite */
	horizontal m_horizontal;    /* direction horizontale */
	state m_state;              /* etat du sprite */
	//Anim_table * m_animm;     /* gestionnaire d'animations */
	uint32_t m_phase;		    /* phase pour alterner les images lors du déplacememnt */
	Sound_manager *m_sound_manager;
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
    virtual SDL_Surface * current_picture() const;

	/*!
	 *	@brief Met à jour la position du sprite
	 *	@param static_data Données du jeu
	 *	@param collisions_manager Gestionnaire de collisions
	*/
    void update_pos(Static_data *static_data, Collisions_manager *collisions_manager);

	/*!
	 *	@brief Accesseur
	 *	@return La position du sprite
	*/
	Rect position() const;

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
	 *	@return La direction horizontale du sprite
	 *
	 *	-1 pour gauche, 0 pour milieu, 1 pour droite
	*/
	int direction_h() const; /* retourne la direction horizontale du sprite (-1 pour gauche, 0 pour middle, 1 pour droite*/
};







#endif
