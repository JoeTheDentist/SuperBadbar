/**
 * 	@file CollisionsManager.h
 * 	@brief header de la classe CollisionsManager
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _COLLISIONS_MANAGER_
#define _COLLISIONS_MANAGER_

#include <stdint.h>
#include <list>
#include "CollisionsMatrix.h"
#include "BindablePlatform.h"
#include "../util/globals.h"
#include "../util/Analyser.h"
#include "../util/debug.h"



class Static;
class BindablePlatform;
class Babar;
class Analyser;

/**
 * 	@class CollisionsManager
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
 * 4 derniers bits (les bits de droite): 1 signifie collision et 0 absence de collision
 * le bit de poids fort représente haut, puis bas, puis gauche, puis droite pour
 * le bit de poids faible
 *
 *	Le premier bit est utile que dans le codage du fichier, il n'a aucun sens quand les
 *	statics ont été chargés
 *
 *	La classe fournit donc des méthodes pour
 *	déterminer la nature de la collision (is_xxxx_collision())
 *
 *	Pour savoir si un sprite peut avancer, on a besoin de connaitre la nature
 *	des cases de collision qui bordent ses extrémités (xxx_collision())
 *

 *	@warning Beaucoup de vérifications sont faites pour éviter les dépassements de tableaux. On peut donc optimiser ici
 */
class CollisionsManager {
private:
	CollisionsMatrix *m_matrix; // la matrice de collision du niveau
	std::list<BindablePlatform *> m_moving_platforms;
	std::list<std::pair<BindablePlatform *, int> > m_waiting_platforms; // plateformes avant respawn
public:

	/**
	 *	@brief Constructeur
	*/
	CollisionsManager();

	/**
	 *	@brief Destructeur
	*/
	~CollisionsManager();

	/**
	 *	@brief Accesseur
	 *	@return La matrice des collisions statiques
	*/
	CollisionsMatrix *get_matrix() { return m_matrix; }

	/**
	 *	@brief Initialisation de la matrice de collision
	 *	@param level Le numéro du niveau �  charger
	*/
	void init_collisions_manager(int level);


	/**
	 *	@brief Initialisation de la matrice de collision
	 *	@param level_name Le chemin vers le fichier level �  charger
	*/
	void init_collisions_manager(std::string level_name);

	/**
	 *	@brief Ajoute une plateforme au CollisionsManager
	 *	@param platform La plateform a ajouter
	 *	@param wait Le temps d'attente avant l'apparition reelle de la plateforme
	 *
	*/
	void addPlatform(BindablePlatform *platform, int wait = 0);

	/**
	 *	@brief Controle la collision de deux rectangles
	 * 	@param A Premier rectangle
	 *	@param B Deuxieme rectangle
	 *	@return Vrai si les deux rectangles sont en collision
	*/
	static bool check_collision(Rect A, Rect B);


	/**
	 *	@brief Affiche les plateformes mobiles
	 *	@param camera Le gestionnaire d'affichage
	*/
	void display_platforms(Camera * const camera) const;

	/**
	 *	@brief Mise �  jour de la position des plateformes
	*/
	void update_platforms_pos();
	/**
	 *	@brief Mise �  jour de la vitesse des plateformes
	*/
	void update_platforms_speed();

	/**
	 *	@brief Lie Babar aux plateformes auxquelles il doit etre lié
	 *	@param babar Babar!
	*/
	void update_babar_platforms();

	/**
	 *	@brief Supprime les plateformes "mortes" (sorties de l'écran etc.)
	*/
	void update_dead_platforms();

	/**
	 *	@brief Met a jour la liste d'attente des plateformes
	*/
	void update_waiting_list();


	/**
	 *	@brief Décode le nombre de collision
	 *	@param coll_number Le nombre de collision
	 *	@return Vrai si la collision codée bloque les déplacements vers le haut
	*/
	static bool is_up_coll(uint32_t coll_number);

	/**
	 *	@brief Décode le nombre de collision
	 *	@param coll_number Le nombre de collision
	 *	@return Vrai si la collision codée bloque les déplacements vers le bas*/
	static bool is_down_coll(uint32_t coll_number);

	/**
	 *	@brief Décode le nombre de collision
	 *	@param coll_number Le nombre de collision
	 *	@return Vrai si la collision codée bloque les déplacements vers la gauche
	*/
	static bool is_left_coll(uint32_t coll_number);

	/**
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
