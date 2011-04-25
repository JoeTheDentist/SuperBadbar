/**
 * 	@file moving_platform.h
 * 	@brief header de la classe Falling_platform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _FALLING_PLATFORM_
#define _FALLING_PLATFORM_

#include <string>
#include <stdint.h>

#include "../video/statics.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../physic/collisions_matrix.h"
#include "../physic/bindable_platform.h"

#define PLATFORM_RESPAWN_TIME 100
class Surface;
class Babar;
class Collisions_manager;
class Camera;


/**
 * 	@class Falling_platform
 * 	@brief Classe représentant une plateforme pouvant tomber
 *
 *	C'est une plateforme bindable qui commence a tomber quand babar monte dessus
 *	Elle respawn un certain temps apres le bind
 */
class Falling_platform : public Bindable_platform {
protected:
	bool m_is_falling;
	Collisions_manager *m_collisions_manager;
	std::string m_file_name; // nom du fichier depuis le dossier des statics sans extension
public:
	
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Un analyser positionne avant la description d'un Falling_platform
	 *	@param Un pointeur vers le collision manager contenant cette falling_platform
	 */
	Falling_platform(Analyser &analyserLevel, Collisions_manager *collisions_manager);

	/**
	 *	@brief Concstructeur
	 *	@param posx La coordonnee x de depart
	 *	@param posy La coordonnee y de depart
	 *	@param file_name Le nom du fichier depuis le dossier des statics sans extension
	 *	@param Un pointeur vers le collision manager contenant cette falling_platform
	*/
	Falling_platform(int posx, int posy, std::string file_name, Collisions_manager *collisions_manager);

	/**
	 * 	@brief Destructeur
	 */
	virtual ~Falling_platform();


	/**
	 * 	@brief Mise à jour de la vitesse
	 *	@todo à coder
	 */
	virtual void update_speed();


	/**
	 *	@brief Lit le Babar a la plateforme et fait tomber la plateforme
	 */
	virtual void bind();
	
protected:
	void begin_fall();
	/*!
	 *	@brief Copie la falling_platform	
	 *	@return La copie
	*/
	Falling_platform *duplicate();

};







#endif
