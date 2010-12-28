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
#include "../util/globals.h"
#include "../video/displayable.h"

class Surface;
class Babar;



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
 *	Si, au cours de l'évolution du jeu on souhaite utiliser plusieurs joueurs,
 *	il faudra remplacer Babar par une liste de Babar
 */
class Moving_platform : public Displayable {
private:
	Surface *m_surface;
	Babar *m_babar;
	Rect m_pos;
	Rect m_speed;
	uint32_t ** m_collisions_matrix;
	int coll_size_w;
	int coll_size_h;
	int m_phase;
public:
	/**
	 * 	@brief Constructeur
	 *	@param filename	Le nom des fichiers images et col sans extension
	 */
	Moving_platform(std::string filename);

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
	void update_pos(Babar *babar);

	/**
	 * 	@brief Mise à jour de la vitesse
	 *	@todo à coder
	 */
	void update_speed();

	/**
	 * 	@brief lie Babar à la plateforme
	 */
	void bind(Babar *babar);
	 
	/**
	 * 	@brief delie Babar de la plateforme
	 */
	void unbind();
	 
	/**
	 * 	@brief Accesseur
	 *	@return L'image actuelle de la plateforme
	 */
	Surface *current_picture() const;
	
	/**
	 * 	@brief Accesseur
	 *	@return La position actuelle de la plateforme
	 */
	Rect position() const;
	
		/**
	 * 	@brief Accesseur
	 *	@return La vitesse actuelle de la plateforme
	 */
	Rect speed() const;
	
	
	 
	/**
	 * 	@brief 
	 */
	bool check_babar(Babar *babar);
	 
	 
	/**
	 * 	@brief 
	 */
	 
	 
	 
};







#endif
