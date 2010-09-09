/**
 * Gestion des évènements: contient la configuration des touches
 * et l'utilise pour gérer les actions déclenchées par le joueur
 **/
 
 /* 
	Rappel : si trop de touches sont appuyées simultanément, certaines ne sont pas détectées
	Solution: changer la configuration des touches (éviter en particulier les fleches directionnelles)
*/

#ifndef _EVENTS_
#define _EVENTS_

enum key { 
	k_none = 0, k_exit, k_up, k_down, k_right, k_left, k_action, k_jump, k_fire //k_fire doit etre le dernier
};

class Events_status {
private:
	enum key m_key_config[SDLK_LAST];
	bool m_key_down[k_fire + 1];
public:
	Events_status();				/* constructeur */  // il faudra le faire à partir d'un fichier de configuration
	~Events_status();				/* destructeur */
	void update_events();			/* met à jour les touches enfoncées à partir des actions du joueur */
	bool key_down (enum key k);		/* retourne vrai si la touche est enfoncée */
	bool key_dir_down();   			/* retourne si une touche gauche droite est enfoncée */          
	void disable_key(enum key k); 	/* fait remonter la touche passée en paramètre */
	void disable_all_keys();		/* fait remonter toutes les touches */

};



#endif
