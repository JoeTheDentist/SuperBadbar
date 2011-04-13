#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

#define GRAVITE 7           /* Constante pour la décélération de saut */
#define DAMAGE_BOX_RATIO 5

/* Différents états du joueur */
enum state_player {
    STATIC, WALK, JUMP, CROUCH, CROUCH_WALKING
};

/* Différents états des monstres */
enum state_m {
    WALKING, WAIT, DEATH
};


enum direction {
    LEFT, RIGHT, UP, DOWN, NOPE
};

#include "../items/weapons.h"
#include "../sprites/sprites.h"
#include "../video/displayable.h"

class Static_data;
class Keyboard;
class Collisions_manager;
class Sprite;

/**
 * 	@class Actor
 * 	@brief Classe mère à tous les acteurs du jeux
 */
class Actor {
protected:
	Rect m_pos; 		/* position du sprite et sa taille */
	Rect m_speed;		/* vitesse du sprite */
	direction m_dir;    /* direction */
	Sprite * m_sprite;  /* Représentation de l'acteur */
	int m_phase;        /* temps depuis création, en nombre de cycle */
public:
	/*!
	 *	@brief Constructeur
	*/
	Actor();

	/*!
	 *	@brief Destructeur
	*/
    virtual ~Actor();

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
	 *	@return La phase du sprite
	*/
	int phase() const;

	/*!
	 *	@brief Accesseur
	 *	@return La direction directione du sprite
	 *
	 *	-1 pour gauche, 0 pour milieu, 1 pour droite
	*/
	int direction_h() const; /* retourne la direction directione du sprite (-1 pour gauche, 0 pour middle, 1 pour droite*/

	direction dir() const;
};


#endif // ACTORS_H_INCLUDED
