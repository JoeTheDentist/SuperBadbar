#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

#define GRAVITE 7           /* Constante pour la décélération de saut */
#define DAMAGE_BOX_RATIO 5
#include "../items/weapons.h"
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
 * 	@class Actor
 * 	@brief Classe mère à tous les acteurs du jeux
 */
class Actor: public Displayable {
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
	Actor();

	/*!
	 *	@brief Destructeur
	*/
	virtual ~Actor();

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


#endif // ACTORS_H_INCLUDED
