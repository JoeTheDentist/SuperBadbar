/**
 * 	@file babar.h
 * 	@brief Header de la classe Babar
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _BABAR_
#define _BABAR_

#include "sprites.h"
#include "../video/animation.h"
#include "../video/anim_manager.h"
#include <list>
#define BABAR_SPEED 15

class Collisions_manager;
class Projectiles_manager;

/**
 * 	@class Babar
 * 	@brief Personnage controlé par un joueur
 *
 *	Les touches enfoncées par l'utilisateur sont récupérées par 
 *	keyboard, dont l'état est utilisé par les méthodes de tir, de saut,
 *	de mise à jour d'état et de vitesse
 *
 *	@todo réorganiser les update\n 
 *	Faire un saut sensible à la longueur de l'appui de la touche\n
 *	Certaines méthodes doivent etre private
 *
 */
class Babar: public Sprite {
protected:
	Keyboard *m_keyboard;	            /* pointeur sur le clavier de Game. C'est Game qui met à jour ce clavier*/
    horizontal m_last_dir;              /* direction vers laquelle Babar regarde (pour les tirs haut et bas) */
    Anim_manager * m_animm;             /* gestionnaire des animations */
	bool m_double_jump;		            /* vaut vrai si Babar est en double saut */
	bool m_plane;						/* vaut vrai si Babar est en train de planer */
	bool m_allowed_to_plane;			
    Weapon m_weapon;		            /* arme actuelle de babar  */
    uint32_t m_fire_phase;	            /* phase du tir */
	int m_lifes;                        /* nombre de vies */
	int m_invincible;                   /* durée d'invicibilité après avoir été touché */
public:
	
	/**
	 * 	@brief Constructeur
	 *	@param keyboard L'utilitaire qui récupère les entrées clavier du joueur
	 *	@param static_data Les données du niveau
	 *	@param sound_manager Le gestionnaire de son
	 */
	Babar(Keyboard *keyboard, Static_data *static_data, Sound_manager *sound_manager);

	/**
	 * 	@brief Destructeur
	 */
	~Babar();

	/**
	 * 	@brief Charge les images de babar
	 *	@param age	L'age de Babar
	 */
	void load(char age); 

	/**
	 * 	@brief Met à jour la vitesse de Babar
	 */
	void update_speed();
	
	/**
	 * 	@brief Met à jour l'état et la direction de Babar
	 *	@param static_data Données du niveau
	 *	@param collisions_manager Gestionnaire de collision
	 */
	void update_state(Static_data *static_data, Collisions_manager *collisions_manager, Projectiles_manager *projectile_manager);   
	
	/**
	 * 	@brief Mise à jour de la direction de Babar en fonction des touches enfoncées
	 */
	void update_direction();

	/**
	 * 	@brief Indique si Babar peut tirer
	 *	@return Vrai si Babar peut tirer
	 *
	 *	On considère que "Babar peut tirer" si la touche
	 *	tirer est enfoncée et s'il est autorisé à tirer
	 */
	bool can_fire() const;
	
	/**
	 * 	@brief Fait tirer Babar
	 *	@return La liste de projectiles tirés
	 *	@todo changer les types de retour et l'organisation de fire et tout ce qui touche au tir
	 */
	std::list<Projectile*> *fire();
	
	/**
	 * 	@brief  Indique si Babar peut faire un double saut
	 *	@return Vrai si Babar peut faire un double saut
	 *
	 *	On considère que "Babar peut faire un double saut" si la touche
	 *	sauter est enfoncée et s'il est autorisé à faire un double saut
	 */
	bool can_double_jump() const;
	
	/**
	 * 	@brief Fait resauter Bababr
	 */
	void double_jump();
	
	/**
	 * 	@brief Indique si Babar peut sauter
	 *	@return Vrai si Babar peut sauter
	 *
	 *	On considère que "Babar peut sauter" si la touche
	 *	sauter est enfoncée et s'il est autorisé à sauter
	 */	
	bool can_jump() const;
	
	/**
	 * 	@brief Fait sauter Babar
	 */
	void jump();
	
	/**
	 * 	@brief Indique si Babar peut traverser la plateforme sur laquelle il est
	 *	@return vrai si bas et espace sont appuyes, si l'état de babar permet de descendre et si babar est sur un objet de collision bas
	 */
	bool can_go_down(Collisions_manager *collisions_manager) const;
	
	/**
	 * 	@brief Effectue la traversee d'une surface de collision bas si elle repond aux criteres de traversee 
	 *	@param collisions_manager Le gestionnaire de collisions
	 */
	void go_down(Collisions_manager *collisions_manager);  

	/**
	 * 	@brief Indique si Babar peut planer
	 *	@return Vrai si Babar peut voler
	 */
	bool can_fly() const;
	
	/**
	 * 	@brief Fait voler Babar
	 */
	void fly();
	
	/**
	 * 	@brief Indique si Babar doit arreter de planer
	 *	@return Vrai si Babar doit arreter de planer
	 */
	bool can_stop_fly() const;
	
	/**
	 * 	@brief Fait arreter babar de planer
	 */
	void stop_fly();
	
	/**
	 * 	@brief Changer l'arme actuelle de Babar
	 *	@param weapon La nouvelle arme
	 */
	void change_weapon(weapon_type weapon);
	
	/**
	 * 	@brief Accesseur
	 *	@return Vrai si Babar est invincible
	 */
	bool is_invincible() const;
	
	/**
	 * 	@brief Accesseur
	 *	@return Le nombre de vies de Babar
	 */
	int lifes() const;
	
	/**
	 * 	@brief Accesseur
	 *	@return Le nombre de munitions de l'arme actuelle de Babar
	 */
	int munitions() const;
	
	/**
	 * 	@brief Accesseur
	 *	@return Le type de l'arme actuelle de Babar
	 */
	weapon_type type_of_weapon() const;
	
	/**
	 * 	@brief Mutateur: fait perdre des vies à Babar
	 *	@param damages Le nombre de vies à faire perdre
	 */
	void damage(int damages);
	
	/**
	 * 	@brief Accesseur
	 *	@return L'image actuelle de Babar
	 */
	SDL_Surface * current_picture() const; 

};

#endif


