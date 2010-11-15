#ifndef _BABAR_
#define _BABAR_

#include "sprites.h"
#define BABAR_SPEED 15

class Babar: public Sprite {
protected:
	Keyboard *m_keyboard;	            /* pointeur sur le clavier de Game. C'est Game qui met à jour ce clavier*/
    horizontal m_last_dir;              /* direction vers laquelle Babar regarde (pour les tirs haut et bas) */
    SDL_Surface *m_pics[3][3][3][4];    /* Images des animations indicés par: état, gauche droite, bas haut, numéro image */
	bool m_double_jump;		            /* vaut vrai si Babar est en double saut */
	bool m_fly;
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
	void fire();						/* fait tirer Babar */
	void double_jump();					/* fait resauter Babar*/
	void jump();						/* fait sauter babar */
	void go_down(Static_data *static_data);     /* effectue la traversee d'une surface de collision bas si elle repond aux criteres de traversee */
	void damage(int damages);

	SDL_Surface * current_picture();  	/* Retourne la bonne image de l'animation */
	bool can_fire();					/* retourne vrai si le joueur appuie sur tirer et s'il peut tirer à ce moment */
	bool can_double_jump();				/* retourne vrai si Babar peut resauter */
	bool can_jump();	/* retourne vrai si le joueur appuie sur saut et s'il peut sauter à ce moment */
	bool can_fly();
	void fly();
	bool can_go_down(Static_data *static_data);		/* retourne vrai si bas et espace sont appuyes, si l'état de babar permet de descendre et si babar est sur un objet de collision bas */
	bool is_invincible();
	int lifes();
	int munitions();
	weapon_type type_of_weapon();
};

#endif


