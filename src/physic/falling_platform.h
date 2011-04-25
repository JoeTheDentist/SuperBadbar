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
