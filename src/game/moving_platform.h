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
#include "../game/collisions_matrix.h"

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
 *	Une plateforme mobile est construite à partir du meme type de fichier qu'un
 *	static: un .col pour la matrice de collisions et une image
 *	Si, au cours de l'évolution du jeu on souhaite utiliser plusieurs joueurs,
 *	il faudra remplacer Babar par une liste de Babar
 */
class Moving_platform : public Static, public Collisions_matrix
{
private:
	Babar *m_babar;
	Rect m_speed;
	Rect m_begin;
	Rect m_end;
//~ 	int coll_size_w;
//~ 	int coll_size_h;
	int m_phase;
public:
	/**
	 * 	@brief Constructeur
	 *	@param filename	Le nom des fichiers images et col sans extension
	 */
	Moving_platform(std::string file_name, int beginx, int beginy, int endx, int endy);

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
	 *	@return La vitesse actuelle de la plateforme
	 */
	Rect speed() const;



	/**
	 * 	@brief Indique si Babar doit etre lié à la plateforme
	 *	@param babar Le Babar à lier
	 *	@return Vrai si Babar doit etre lié à la plateforme courante
	 */
	bool check_babar(Babar *babar);


	/**
	 * 	@brief
	 */



};







#endif
