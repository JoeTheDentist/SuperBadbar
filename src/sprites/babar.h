#ifndef _BABAR_
#define _BABAR_

#include "sprites.h"


class Babar: public Sprite {
protected:
	Keyboard *m_keyboard;	/* pointeur sur le clavier de Game. C'est Game qui met à jour ce clavier*/
    horizontal m_last_dir;  /* direction vers laquelle Babar regarde (pour les tirs haut et bas) */
    SDL_Surface *m_pics[3][3][3][2]; /* Images des animations indicés par: état, gauche droite, bas haut, numéro image */
	bool m_double_jump;		/* vaut vrai si Babar est en double saut */
    Weapon m_weapon;		/* arme actuelle de babar  */
    uint32_t m_fire_phase;	/* phase du tir */ 
	int m_lifes;
	int m_invincible;
public:
	Babar(List<Projectile*> *projectiles_friend, Keyboard *keyboard, Static_data *static_data, Sound_manager *sound_manager);/* constructeur */
	~Babar();							/* destructeur */
	SDL_Surface * current_picture();  	/* Retourne la bonne image de l'animation */
	void update_speed();				/* mise à jour de la vitesse en fonction des touches enfoncées */
	void update_state(Static_data *static_data);    /* mise à jour de l'état de babar et de sa direction */
	void update_direction();			/* mise à jour de la direction de babar en fonction des touches enfoncées*/
	bool can_fire();					/* retourne vrai si le joueur appuie sur tirer et s'il peut tirer à ce moment */
	void fire();						/* fait tirer Babar */
	bool can_double_jump();				/* retourne vrai si Babar peut resauter */
	void double_jump();					/* fait resauter Babar*/
	bool can_jump();					/* retourne vrai si le joueur appuie sur saut et s'il peut sauter à ce moment */
	void jump();						/* fait sauter babar */
	bool can_go_down(Static_data *static_data);		/* retourne vrai si bas et espace sont appuyes, si l'état de babar permet de descendre et si babar est sur un objet de collision bas */
	void go_down(Static_data *static_data);			/* effectue la traversee d'une surface de collision bas si elle repond aux criteres de traversee */
	void damage(int damages);
	bool is_invincible();
	int lifes();
};

#endif


