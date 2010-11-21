#ifndef _BABAR_
#define _BABAR_

#include "sprites.h"
#include "../video/animation.h"
#define BABAR_SPEED 15

class Babar: public Sprite {
protected:
	Keyboard *m_keyboard;	            /* pointeur sur le clavier de Game. C'est Game qui met à jour ce clavier*/
    horizontal m_last_dir;              /* direction vers laquelle Babar regarde (pour les tirs haut et bas) */
    Animation * test;
    Animation * m_anim[3][2][2];        /* Animations : etat, gauche-droite, haut-bas */

	bool m_double_jump;		            /* vaut vrai si Babar est en double saut */
	bool m_plane;						/* vaut vrai si Babar est en train de planer */
	bool m_allowed_to_plane;
    Weapon m_weapon;		            /* arme actuelle de babar  */
    uint32_t m_fire_phase;	            /* phase du tir */
	int m_lifes;                        /* nombre de vies */
	int m_invincible;                   /* durée d'invicibilité après avoir été touché */
public:
	Babar(List<Projectile*> *projectiles_friend, Keyboard *keyboard, Static_data *static_data, Sound_manager *sound_manager);/* constructeur */
	~Babar();							/* destructeur */
	void load(char age);                 /* Fonction qui permet le chargement des images de babar voulues */
	void update_speed();				/* mise à jour de la vitesse en fonction des touches enfoncées */
	void update_state(Static_data *static_data);    /* mise à jour de l'état de babar et de sa direction */
	void update_direction();			/* mise à jour de la direction de babar en fonction des touches enfoncées*/
	bool can_fire();
	void fire();	/* fait tirer Babar */
	bool can_double_jump();				/* retourne vrai si Babar peut resauter */
	void double_jump();					/* fait resauter Babar*/
	bool can_jump();	/* retourne vrai si le joueur appuie sur saut et s'il peut sauter à ce moment */
	void jump();						/* fait sauter babar */
	bool can_go_down(Static_data *static_data);		/* retourne vrai si bas et espace sont appuyes, si l'état de babar permet de descendre et si babar est sur un objet de collision bas */
	void go_down(Static_data *static_data);     /* effectue la traversee d'une surface de collision bas si elle repond aux criteres de traversee */
	bool can_fly();
	void fly();
	bool can_stop_fly();
	void stop_fly();
	void change_weapon(weapon_type weapon);
	bool is_invincible();
	int lifes();
	int munitions();
	weapon_type type_of_weapon();
	void damage(int damages);
	SDL_Surface * current_picture();  	/* Retourne la bonne image de l'animation */

};

#endif


