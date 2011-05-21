/**
 * 	@file chained_platform.h
 * 	@brief header de la classe Chained_platform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */

#ifndef _CHAINED_PLATFORM_
#define _CHAINED_PLATFORM_

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
 * 	@class Chained_platform
 * 	@brief Classe représentant une plateforme mobile
 *	@warning Not implemented
 *	@todo Not implemented
 *	C'est une plateforme bindable qui se deplace circulairement
 */
class Chained_platform : public Bindable_platform {
protected:
	Rect m_center;
	int m_chain_length;
public:
	
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Un analyser positionne avant la description d'un Chained_platform
	 */
	Chained_platform(Analyser &analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	virtual ~Chained_platform();


	/**
	 * 	@brief Mise à jour de la vitesse
	 *	@todo à coder
	 */
	virtual void update_speed();



};







#endif
