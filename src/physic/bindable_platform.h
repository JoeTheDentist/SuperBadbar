/**
 * 	@file bindable_platform.h
 * 	@brief header de la classe Bindable_platform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date avril 2011
 *
 */

#ifndef _BINDABLE_PLATFORM_
#define _BINDABLE_PLATFORM_

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
 * 	@class Bindable_platform
 * 	@brief Classe représentant une plateforme de collision potentiellement mobile
 *
 *	Elle peut etre affichée, se déplace et contient des données de collision
 *	Babar est le seul sprite en intéraction avec la plateforme.
 *	Lorsque Babar tombe sur la plateforme, il est liée à elle
 *	Dans ce cas, il suit ses déplacements jusqu'à son prochain son
 * 	ou sa chute de la plateforme. La plateforme "sait" si elle est liée
 *	ou pas à Babar.
 *	Une plateforme mobile est construite à partir du meme type de fichier qu'un
 *	static: un .col pour la matrice de collisions et une image
 */
class Bindable_platform : public Static, public Collisions_matrix
{
protected:
	Babar *m_babar;
	Rect m_speed;
	int m_phase;
	int m_can_bind;
public:
	
	/**
	 * 	@brief Constructeur
	 */
	Bindable_platform();

	/**
	 * 	@brief Destructeur
	 */
	~Bindable_platform();

	/**
	 * 	@brief Initialise le bindable_platform
	 *	@param posx La position x du bindable 
	 *	@param posy La position y du bindable 
	 *	@param file_name Le nom du fichier depuis les statics
	 */	
	void init_bindable_platform(int posx, int posy, std::string file_name);

	/**
	 * 	@brief Mise à jour de la position
	 *	@param babar Un personnage controle par le joueur
	 *
	 *	Detecte la collision avec babar par le bas pour éventuellement le lier
	 */
	void update_pos();

	/**
	 * 	@brief Mise à jour de la vitesse
	 */
	virtual void update_speed();

	/**
	 * 	@brief lie Babar à la plateforme
	 */
	virtual void bind();

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
