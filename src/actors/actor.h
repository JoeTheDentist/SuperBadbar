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

class StaticData;
class Keyboard;
class CollisionsManager;
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
	 *	@param StaticData Données du jeu
	 *	@param CollisionsManager Gestionnaire de collisions
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

	/*!
	*	@brief Accesseur
	*	@return La direction du sprite
	*/
	direction dir() const;

	/*!
	*	@brief Accesseur
	*	@return La position du centre du rectangle de l'acteur
	*
	*	Les champs h et w du retour n'ont pas de sens
	*/
	Rect center() const;

	/*!
	 *	@brief Mutateur: augmente la position de l'actor de x et y sans tenir compte des collisions
	 *	@param x Le deplacement x
	 *	@param y Le deplacement y
	 *
	 *	move et set_pos sont les seules methodes pouvant directement modifier la position de l'actor
	*/
	virtual void move(int x, int y);

	/*!
	 *	@brief Mutateur: met a jour la position de l'actor de x et y sans tenir compte des collisions
	 *	@param x Le nouveau x
	 *	@param y Le nouveau y
	 *
	 *	move et set_pos sont les seules methodes pouvant directement modifier la position de l'actor
	*/
	virtual void set_pos(int x, int y);

	virtual void do_stay_in_level();

};


#endif // ACTORS_H_INCLUDED
