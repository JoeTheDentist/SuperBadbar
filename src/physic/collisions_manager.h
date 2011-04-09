/**
 * 	@file collisions_manager.h
 * 	@brief header de la classe Collisions_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _COLLISIONS_MANAGER_
#define _COLLISIONS_MANAGER_

#include <stdint.h>
#include <list>
#include "collisions_matrix.h"
#include "moving_platform.h"
#include "../util/globals.h"
#include "../util/analyser.h"
#include "../util/debug.h"

class Static;
class Moving_platform;
class Babar;
class Analyser;

/**
 * 	@class Collisions_manager
 * 	@brief Classe gérant les collisions
 *
 *	Contient la matrice de collisions du niveau
 *	ainsi que les méthodes de collision utilisées dans le jeu
 *
 *	Une case de collision peut etre (simultanément):
 *	- bloquante par le bas
 *	- bloquante par le haut
 *	- bloquante par la droite
 *	- bloquante par la gauche
 *
 * Un nombre de collision caractérise la collision: on regarde les
 * 4 derniers bits: 1 signifie collision et 0 absence de collision
 * le bit de poids fort représente haut, puis bas, puis gauche, puis droite pour
 * le bit de poids faible
 *
 *	La classe fournit donc des méthodes pour
 *	déterminer la nature de la collision (is_xxxx_collision())
 *
 *	Pour savoir si un sprite peut avancer, on a besoin de connaitre la nature
 *	des cases de collision qui bordent ses extrémités (xxx_collision())
 *

 *	@warning Beaucoup de vérifications sont faites pour éviter les dépassements de tableaux. On peut donc optimiser ici
 */
class Collisions_manager {
private:
	Collisions_matrix *m_matrix; // la matrice de collision du niveau
	std::list<Moving_platform *> m_moving_platforms;
public:

	/*!
	 *	@brief Constructeur
	*/
	Collisions_manager();

	/*!
	 *	@brief Destructeur
	*/
	~Collisions_manager();

	/*!
	 *	@brief Accesseur
	 *	@return La matrice des collisions statiques
	*/
	Collisions_matrix *get_matrix() { return m_matrix; }

	/*!
	 *	@brief Initialisation de la matrice de collision
	 *	@param level Le numéro du niveau à charger
	*/
	void init_collisions_manager(int level);


	/*!
	 *	@brief Initialisation de la matrice de collision
	 *	@param level_name Le chemin vers le fichier level à charger
	*/
	void init_collisions_manager(std::string level_name);



	/*!
	 *	@brief Controle la collision de deux rectangles
	 * 	@param A Premier rectangle
	 *	@param B Deuxieme rectangle
	 *	@return Vrai si les deux rectangles sont en collision
	*/
	static bool check_collision(Rect A, Rect B);


	/*!
	 *	@brief Affiche les plateformes mobiles
	 *	@param camera Le gestionnaire d'affichage
	*/
	void display_platforms(Camera * const camera) const;

	/*!
	 *	@brief Mise à jour de la position des plateformes
	*/
	void update_platforms_pos();
	/*!
	 *	@brief Mise à jour de la vitesse des plateformes
	*/
	void update_platforms_speed();

	/*!
	 *	@brief Lie Babar aux plateformes auxquelles il doit etre lié
	 *	@param babar Babar!
	*/
	void update_babar_platforms();



	/*!
	 *	@brief Supprime les plateformes "mortes" (sorties de l'écran etc.)
	*/
	void update_dead_platforms();


	/*!
	 *	@brief Décode le nombre de collision
	 *	@param coll_number Le nombre de collision
	 *	@return Vrai si la collision codée bloque les déplacements vers le haut
	*/
	static bool is_up_coll(uint32_t coll_number);

	/*!
	 *	@brief Décode le nombre de collision
	 *	@param coll_number Le nombre de collision
	 *	@return Vrai si la collision codée bloque les déplacements vers le bas*/
	static bool is_down_coll(uint32_t coll_number);

	/*!
	 *	@brief Décode le nombre de collision
	 *	@param coll_number Le nombre de collision
	 *	@return Vrai si la collision codée bloque les déplacements vers la gauche
	*/
	static bool is_left_coll(uint32_t coll_number);

	/*!
	 *	@brief Décode le nombre de collision
	 *	@param coll_number Le nombre de collision
	 *	@return Vrai si la collision codée bloque les déplacements vers la droite
	*/
	static bool is_right_coll(uint32_t coll_number);
	
	#ifdef DEBUG_COLL
	void display_coll(Camera *camera);
	#endif
	
private:
	void init_statics(Analyser &analyser);
	void init_moving_plateforms(Analyser &analyser);
};



#endif
