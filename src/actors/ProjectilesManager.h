/**
 * 	@file ProjectilesManager.h
 * 	@brief Header de la classe ProjectilesManager
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _ProjectilesManager
#define _ProjectilesManager

#include <list>

/* Canaux des groupes de dommage, on pourra utiliser la suite pour les diff√©rents joueurs */
enum dmg_chan {
    ALL, MONSTERS, PLAYER1, PLAYER2, PLAYER3, PLAYER4, LAST_dmg_chan
};

class Projectile;
class StaticData;
class CollisionsManager;
class Camera;

/**
 * 	@class ProjectilesManager
 * 	@brief Gestionnaire de projectiles
 *
 *	@warning pour le moment on ne dispose que des projectiles de babar
 *
 *	La version actuelle diff√©rencie deux types de projectiles:\n
 *	- Ceux du h√©ros et de ses √©ventuels amis
 *	- Ceux des ennemis du h√©ros
 *
 *	Le h√©ros est sensible aux projectiles de ses ennemis et vice versa
 */
class ProjectilesManager {
private:
	std::list<Projectile*> m_proj[LAST_dmg_chan];
public:

	/**
	 *	@brief Constructeur
	*/
	ProjectilesManager();

	/**
	 *	@brief Destructeur
	*/
	~ProjectilesManager();

	/**
	 *	@brief Met √  jour la position de l'ensemble des projectiles
	*/
	void update_pos();

	/**
	 *	@brief Met √  jour la vitesse de l'ensemble des projectiles
	*/
	void update_speed();

	/**
	 *	@brief Met √  jour les √©tats de l'ensemble des projectiles
	*/
	void update_state();

	/**
	 *	@brief Supprime les projectiles √  supprimer
	 *	@param StaticData Les donn√©es du niveau
	*/
	void delete_old_projectiles();

	/**
	 *	@brief Ajoute un projectile √  la liste des projectiles sur un channel
	 *	@param proj un pointeur vers le projectile √  ajouter
	*/
	void add_proj(Projectile *proj, dmg_chan chan);

	/**
	 *	@brief Vide la liste pass√©e en parametre dans la liste des projectiles sur un channel
	 *	@param proj un pointeur vers la liste de projectiles √  ajouter
	*/
	void add_proj(std::list<Projectile*> *proj, dmg_chan chan);

	/**
	 *	@brief Accesseur
	 *	@return Iterator pointant sur le d√©but de la liste de projectiles amis
	 *	@todo voir si on peut rendre cette methode constante
	*/
	std::list<Projectile *>::iterator proj_begin(dmg_chan chan);

	/**
	 *	@brief Accesseur
	 *	@return Iterator pointant sur la fin de la liste de projectiles amis
	*/
	std::list<Projectile *>::iterator proj_end(dmg_chan chan);
};


#endif
