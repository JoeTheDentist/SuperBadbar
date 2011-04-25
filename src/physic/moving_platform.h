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
#include "../physic/bindable_platform.h"

class Surface;
class Babar;
class Camera;


/**
 * 	@class Moving_platform
 * 	@brief Classe représentant une plateforme mobile
 *
 *	C'est une plateforme bindable qui se deplace
 */
class Moving_platform : public Bindable_platform {
protected:
	Rect m_begin;
	Rect m_end;
public:
	
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Un analyser positionne avant la description d'un Moving_platform
	 */
	Moving_platform(Analyser &analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	virtual ~Moving_platform();


	/**
	 * 	@brief Mise à jour de la vitesse
	 *	@todo à coder
	 */
	virtual void update_speed();



};







#endif
