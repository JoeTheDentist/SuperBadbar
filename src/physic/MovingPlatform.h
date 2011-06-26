/**
 * 	@file MovingPlatform.h
 * 	@brief header de la classe MovingPlatform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _MOVING_PLATFORM_
#define _MOVING_PLATFORM_

#include <string>
#include <stdint.h>

#include "../video/Statics.h"
#include "../util/debug.h"
#include "../util/Analyser.h"
#include "../physic/CollisionsMatrix.h"
#include "../physic/BindablePlatform.h"

class Surface;
class Babar;
class Camera;


/**
 * 	@class MovingPlatform
 * 	@brief Classe représentant une plateforme mobile
 *
 *	C'est une plateforme bindable qui se deplace
 */
class MovingPlatform : public BindablePlatform {
protected:
	Rect m_begin;
	Rect m_end;
public:

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Un analyser positionne avant la description d'un MovingPlatform
	 */
	MovingPlatform(Analyser &analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	virtual ~MovingPlatform();


	/**
	 * 	@brief Mise à jour de la vitesse
	 *	@todo à coder
	 */
	virtual void update_speed();



};







#endif
