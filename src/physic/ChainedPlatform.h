/**
 * 	@file ChainedPlatform.h
 * 	@brief header de la classe ChainedPlatform
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
#include "../physic/CollisionsMatrix.h"
#include "../physic/BindablePlatform.h"

class Surface;
class Babar;
class Camera;


/**
 * 	@class ChainedPlatform
 * 	@brief Classe représentant une plateforme mobile
 *	@warning Not implemented
 *	@todo Not implemented
 *	C'est une plateforme bindable qui se deplace circulairement
 */
class ChainedPlatform : public BindablePlatform {
protected:
	Rect m_center;
	int m_chain_length;
public:

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Un analyser positionne avant la description d'un ChainedPlatform
	 */
	ChainedPlatform(Analyser &analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	virtual ~ChainedPlatform();


	/**
	 * 	@brief Mise à jour de la vitesse
	 *	@todo à coder
	 */
	virtual void update_speed();



};







#endif
