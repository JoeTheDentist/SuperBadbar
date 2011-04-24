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

class Surface;
class Babar;
class Camera;


/**
 * 	@class Falling_platform
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
class Falling_platform : public Bindable_platform {
protected:
	Rect m_begin;
	Rect m_end;
	bool m_is_falling;
public:
	
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Un analyser positionne avant la description d'un Falling_platform
	 */
	Falling_platform(Analyser &analyserLevel);

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

};







#endif
