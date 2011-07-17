/**
 * 	@file MovingPlatform.h
 * 	@brief header de la classe FallingPlatform
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _FALLING_PLATFORM_
#define _FALLING_PLATFORM_

#include <string>
#include <stdint.h>

#include "../video/Statics.h"
#include "../util/debug.h"
#include "../util/Analyser.h"
#include "../physic/CollisionsMatrix.h"
#include "../physic/BindablePlatform.h"

#define PLATFORM_RESPAWN_TIME 100
class Surface;
class Babar;
class CollisionsManager;
class Camera;


/**
 * 	@class FallingPlatform
 * 	@brief Classe repr√©sentant une plateforme pouvant tomber
 *
 *	C'est une plateforme bindable qui commence a tomber quand babar monte dessus
 *	Elle respawn un certain temps apres le bind
 */
class FallingPlatform : public BindablePlatform {
protected:
	bool m_is_falling;
	int m_counter;
	CollisionsManager *m_collisions_manager;
	std::string m_file_name; // nom du fichier depuis le dossier des statics sans extension
public:

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Un analyser positionne avant la description d'un FallingPlatform
	 *	@param Un pointeur vers le collision manager contenant cette FallingPlatform
	 */
	FallingPlatform(Analyser &analyserLevel, CollisionsManager *CollisionsManager);

	/**
	 *	@brief Concstructeur
	 *	@param posx La coordonnee x de depart
	 *	@param posy La coordonnee y de depart
	 *	@param file_name Le nom du fichier depuis le dossier des statics sans extension
	 *	@param Un pointeur vers le collision manager contenant cette FallingPlatform
	*/
	FallingPlatform(int posx, int posy, std::string file_name, CollisionsManager *CollisionsManager);

	/**
	 * 	@brief Destructeur
	 */
	virtual ~FallingPlatform();


	/**
	 * 	@brief Mise √  jour de la vitesse
	 *	@todo √  coder
	 */
	virtual void update_speed();


	/**
	 *	@brief Lit le Babar a la plateforme et fait tomber la plateforme
	 */
	virtual void bind();

protected:
	void begin_fall();
	/**
	 *	@brief Copie la FallingPlatform
	 *	@return La copie
	*/
	FallingPlatform *duplicate();

};







#endif
