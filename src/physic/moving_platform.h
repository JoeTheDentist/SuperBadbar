/**
 * 	@file moving_platform.h
 * 	@brief header de la classe Moving_platform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _MOVING_PLATFORM_
#define _MOVING_PLATFORM_

#include <string>
#include <stdint.h>

#include "../video/statics.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../physic/collisions_matrix.h"

class Surface;
class Babar;
class Camera;


/**
 * 	@class Moving_platform
 * 	@brief Classe représentant une plateforme mobile
 *
 *	Elle peut etre affichée, se déplace et contient des données de collision
 *	Babar est le seul sprite en intéraction avec la plateforme.
 *	Lorsque Babar tombe sur la plateforme, il est liée à elle
 *	Dans ce cas, il suit ses déplacements jusqu'à son prochain son
 * 	ou sa chute de la plateforme. La plateforme "sait" si elle est liée
 *	ou pas à Babar.
 *	Une plateforme mobile est construite à partir du meme type de fichier qu'un
 *	static: un .col pour la matrice de collisions et une image
 *	Si, au cours de l'évolution du jeu on souhaite utiliser plusieurs joueurs,
 *	il faudra remplacer Babar par une liste de Babar
 */
class Moving_platform : public Static, public Collisions_matrix
{
protected:
	Babar *m_babar;
	Rect m_speed;
	Rect m_begin;
	Rect m_end;
	int m_phase;
	bool m_falling_platform;
	bool m_is_falling;
	int m_can_bind;
public:
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Un analyser positionne avant la description d'un Moving_platform
	 */
	Moving_platform(Analyser &analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Moving_platform();

	/**
	 * 	@brief Mise à jour de la position
	 *	@param babar Un personnage controle par le joueur
	 *	@todo à coder
	 *
	 *	Detecte la collision avec babar par le bas pour éventuellement le lier
	 */
	void update_pos();

	/**
	 * 	@brief Mise à jour de la vitesse
	 *	@todo à coder
	 */
	void update_speed();

	/**
	 * 	@brief lie Babar à la plateforme
	 */
	void bind();

	/**
	 * 	@brief delie Babar de la plateforme
	 */
	void unbind();


    /**
	 * 	@brief Accesseur
	 *	@return La vitesse actuelle de la plateforme
	 */
	Rect speed() const;
	
	bool is_going_down();


	/**
	 * 	@brief Indique si Babar doit etre lié à la plateforme
	 *	@return Vrai si Babar doit etre lié à la plateforme courante
	 */
	bool check_babar();

	/*!
	 *	@brief Indique si la plateforme doit etre supprimee
	 *	@return Vrai si oui
	 */
	bool dead();

	/**
	 * 	@brief Indique si la plateforme est en état d'etre liee
	 *	@return Vrai si la plateforme peut etre liee
	 */
	bool can_bind();

	#ifdef DEBUG_COLL
	void display_coll(Camera *camera);
	#endif

};







#endif
