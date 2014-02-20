/**
 * 	@file Actor.h
 * 	@brief Header de la classe Actor
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date Mars 2011
 *
 */

#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

#define GRAVITE 7           /* Constante pour la deceletion de saut */
#define DAMAGE_BOX_RATIO 5

/* Differents ets du joueur */
enum state_player
{
    STATIC, WALK, JUMP, CROUCH, CROUCH_WALKING
};

/* Diffents etats des monstres */
enum state_m
{
    WALKING, WAIT, DEATH
};


enum Direction
{
    LEFT, RIGHT, UP, DOWN, NOPE
};


#include <util/Rect.h>

class StaticData;
class Keyboard;
class CollisionsManager;
class Sprite;

/**
 *  @class Actor
 *  @brief Classe mere de tous les acteurs du jeux
 *
 *  Cette classe represente les acteurs du jeux, toute entie ayant
 *  une logique de mouvement (pos, speed) et d'afficahge (sprite)
 */
class Actor
{
protected:
    Rect m_pos; 		/* position du sprite et sa taille */
    Rect m_speed;		/* vitesse du sprite */
    Direction m_dir;    /* direction */
    Sprite * m_sprite;  /* Representation de l'acteur */
    int m_phase;        /* temps depuis creation, en nombre de cycle */
public:
    /**
     *	@brief Constructeur
    */
    Actor();

    /**
     *	@brief Destructeur
    */
    virtual ~Actor();

    /**
     *	@brief Met a jour la position du sprite
     *	@param StaticData Donnees du jeu
     *	@param CollisionsManager Gestionnaire de collisions
    */
    void update_pos();

    /**
     *	@brief Accesseur
     *	@return La position du sprite
    */
    virtual Rect position() const;


    Rect damage_box() const;

    /**
     *	@brief Accesseur
     *	@return La phase du sprite
    */
    int phase() const;

    /**
     *	@brief Accesseur
     *	@return La direction directione du sprite
     *
     *	-1 pour gauche, 0 pour milieu, 1 pour droite
    */
    int direction_h() const;

    /**
    *	@brief Accesseur
    *	@return La direction du sprite
    */
    Direction getDirection() const;

    /**
    *	@brief Accesseur
    *	@return La position du centre du rectangle de l'acteur
    *
    *	Les champs h et w du retour n'ont pas de sens
    */
    Rect center() const;

    /**
     *	@brief Mutateur: augmente la position de l'actor de x et y sans tenir compte des collisions
     *	@param x Le deplacement x
     *	@param y Le deplacement y
     *
     *	move et set_pos sont les seules methodes pouvant directement modifier la position de l'actor
    */
    virtual void move (int x, int y);

    /**
     *	@brief Mutateur: met a jour la position de l'actor de x et y sans tenir compte des collisions
     *	@param x Le nouveau x
     *	@param y Le nouveau y
     *
     *	move et set_pos sont les seules methodes pouvant directement modifier la position de l'actor
    */
    virtual void set_pos (int x, int y);

    /**
     *  TOCOMMENT
     */
    virtual void do_stay_in_level();

};


#endif // ACTORS_H_INCLUDED
