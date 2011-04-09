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
#include "../sound/sonorisable.h"
#include "../util/analyser.h"
#include "../video/anim_pic.h"
#include "../video/anim_table.h"
#include <list>
#define BABAR_SPEED 15
#define JUMP_TIME 6
#define SOURCE_Y 30  /* décalage en y de la source, par rapport au haut */

class Collisions_manager;
class Projectiles_manager;
class Analyser;
class Gun;
class Weapons_armory;
class Moving_platform;
#include "../items/weapons_armory.h"


enum state_player {
    STATIC, WALK, JUMP, CROUCH, CROUCH_WALKING
};

/**
 * 	@class Babar
 * 	@brief Personnage controlé par un joueur
 *
 *	Les touches enfoncées par l'utilisateur sont récupérées par
 *	keyboard, dont l'état est utilisé par les méthodes de tir, de saut,
 *	de mise à jour d'état et de vitesse
 *
 *	@todo réorganiser les update\n
 *	Certaines méthodes doivent etre private\n
 *	Une méthode doit renvoyer le tir au projectiles manager, au lieu de prendre le projectiles_manager en parametre
 *
 */
class Babar: public Sprite, public Sonorisable {
protected:
    state_player m_state;
    uint32_t m_fire_phase;	            /* phase du tir */
	int m_lifes;                        /* nombre de vies */
	int m_invincible;                   /* durée d'invicibilité après avoir été touché */
	int m_crouch_time;                  /* durée depuis laquelle le joueur demande à être accroupis */
	bool m_ready_double_jump;           /* booléen autorisant le double saut */
	bool m_ready_jump;                  /* booleen autorisant le saut */
	bool m_jump;						/* indique que le joueur est en cours de saut (sa vitesse augment) */
	bool m_double_jump;		            /* vaut vrai si Babar est en cours de double saut */

	Weapons_armory m_weapons_armory;
	Moving_platform *m_bind;			/* plateforme à laquelle est lié Babar (s'il y en a une) */
	Rect m_rel_pos;					/* position dans le référentiel de la plateforme m_bind (si m_bind != NULL)*/
	bool m_fire;                        /* booléen indiquant si Babar est en train de tirer */
	int m_peanuts;

	/**
	 * 	@brief Charge les images de babar
	 *	@param age	L'age de Babar
	 */
	void load_anim(char age);
	bool is_on_something();
public:

	/**
	 * 	@brief Constructeur
	 *	@param keyboard L'utilitaire qui récupère les entrées clavier du joueur
	 *	@param static_data Les données du niveau
	 *	@param sound_manager Le gestionnaire de son
	 *  @param analyser ouvert sur un fichier lvl, en l'occurence du premier level
	 */
	Babar(Analyser *analyser);

	/**
	 * 	@brief Destructeur
	 */
	~Babar();

	/**
	 *  @brief Charge les attributs de Babar propre au lvl
	 *  @param a Analyser ouvert sur le fichier level contenant les coordonnées et l'age de Babar
	 */
	void init_babar(Analyser * a);

	/*!
	 *	@brief Surcharge de l'accesseur de sprite pour avoir la position meme quand babar est binded
	 * 	@return La position actuelle de babar
	*/
	virtual Rect position() const;

	virtual void move(int x, int y);

	/*!
	 *	@brief Met à jour la position du sprite
	 *	@param static_data Données du jeu
	 *	@param collisions_manager Gestionnaire de collisions
	*/
    void update_pos();


	/**
	 * 	@brief Met à jour la vitesse de Babar
	 */
	void update_speed();

	/**
	 * 	@brief Met à jour l'état et la direction de Babar
	 *	@param static_data Données du niveau
	 *	@param collisions_manager Gestionnaire de collision
	 *	@param projectiles_manager Gestionnaire des projectiles
	 */

	void update_state();

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
	bool can_fire();

	/**
	 * 	@brief Fait tirer Babar
	 *	@return La liste de projectiles tirés
	 */
	std::list<Projectile*> *fire();

	/**
	 *  @brief si le joueur demande a marcher et qu'il n'y a rien d'autre
	 */
	bool can_walk() const;



    /**
	 *  @brief si le joueur demande a s'accroupir
	 */
	bool can_crouch() const;

	/**
	 *  @brief fait s'accroupir
	 */
	void crouch();

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
	 * 	@brief Indique si Babar peut traverser la plateforme sur laquelle il est
	 *	@return vrai si bas et espace sont appuyes, si l'état de babar permet de descendre et si babar est sur un objet de collision bas
	 */
	bool can_go_down() const;

	/**
	 * 	@brief Effectue la traversee d'une surface de collision bas si elle repond aux criteres de traversee
	 *	@param collisions_manager Le gestionnaire de collisions
	 */
	void go_down();

	/**
	 * 	@brief Donne une nouvelle arme à Babar
	 *	@param weapon La nouvelle arme
	 */
	void add_weapon(weapon_type weapon);

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
	int munitions() ;

	/**
	 * 	@brief Accesseur
	 *	@return Le type de l'arme actuelle de Babar
	 */
	weapon_type type_of_weapon();

	/**
	 * 	@brief Mutateur: fait perdre des vies à Babar et le rend invincible qq secondes
	 *	@param damages Le nombre de vies à faire perdre
	 */
	void damage(int damages);

	/**
	 * 	@brief Mutateur: fait gagner des vies à Babar
	 *	@param life Le nombre de vies à faire gagner
	 */
	void lifeup(int life);

	/**
	 * 	@brief Accesseur
	 *	@return L'image actuelle de Babar
	 */
	Surface * current_picture() const;

	/**
	 * 	@brief Accesseur
	 *	@return La vitesse actuelle de Babar
	 */
	Rect speed() const;


	/**
	 * 	@brief Accesseur
	 *	@return Return vrai si babar est lié à une plateforme
	 */
	bool binded() const;

	/**
	 * 	@brief Lie babar à la plateforme
	 *	@param platform plateforme à lier
	 */
	void bind(Moving_platform *platform);

	/**
	 * 	@brief Délie babar de sa plateforme
	 */
	void unbind();

	/**
	 * 	@brief Accesseur
	 *	@return Le nombre de cacahuetes possede par babar
	 */
	int peanuts();

	/**
	 * 	@brief Mutateur: incremente le nombre de cacahutes
	 *	@param peanuts Le nombre de cacahuetes a ajouter
	 */
	void incr_peanuts(int peanuts);

	state_player get_state() const;

	void interrupt_jump();

	void interrupt_crouch();

	// check et fait l'unbind
	bool check_unbind();
};

#endif


