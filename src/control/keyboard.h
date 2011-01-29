/**
 * 	@file keyboard.h
 * 	@brief header de la Classe Keyboard
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _KEYBOARD_
#define _KEYBOARD_

#include "SDL/SDL.h"

#include <string>


enum key { 
	k_none = 0, k_exit, k_up, k_down, k_right, k_left, k_next_weapon, k_prev_weapon, k_action, k_jump, k_fire //k_fire doit etre le dernier
};

class Analyser;

/**
 * 	@class Keyboard
 *	@brief Gestion des évènement claviers
 * 
 *	La classe Keyboard met à jour le tableau des touches enfoncées. 
 *	Les touches gérées sont: quitter, haut, bas, droite, gauche, action,
 * 	saut, tir.\n
 *	Elle fournit un accesseur vers l'état de ces touches.\n
 *	Elle permet également de forcer la désactivation d'une ou plusieurs
 *	touches part l'appel d'une méthode (disable_key, disable_all)
 *
 * 	@todo Enlever les touches inutiles, charger les touches depuis 
 *	un fichier de configuration, donner la possibilité au joueur 
 * 	de choisir ses touches avec un menu
 *
 *	@warning Si trop de touches sont appuyées simultanément, certaines ne sont pas détectées.\n
 *	Solution: changer la configuration des touches (éviter en particulier les fleches directionnelles)
 **/
class Keyboard {
	
private:
	enum key m_key_config[SDLK_LAST];	// tableau de configuration des touches
	int m_key_down[k_fire + 1];		// tableau des touches enfoncées	
	bool m_record_on, m_replay_on; 	// indique si les entr�es doivent etre enregistr�es (resp lues)
	Analyser *m_analyser;			// analyser si m_replay_on vaut vrai
public:
	/*!
	* 	@brief Constructeur 
	*	@param record_on Si vrai, le clavier sauvegarde les entrees dans file_name
	*	@param replay_on Si vrai, le clavier lit les entrees dans file_name
	*	@param file_name Chemin du fichier d'input ou output � partir du r�pertoire courant
	*/
	Keyboard(bool record_on, bool replay_on,  std::string output_name, std::string input_name);

	/*!
	* 	@brief Destructeur 
	*/
	~Keyboard();

	/*!
	* 	@brief Met à jour le tableau des touches enfoncées
	*/
	void update_events();			

	/*!
	* 	@brief Accesseur 
	*	@param k la touche a controler
	*	@return Vrai si la touche est enfoncée
	*/
	bool key_down (enum key k) const;

	/*!
	* 	@brief Accesseur 
	*	@param k la touche a controler
	*	@return Le nombre de cycles depuis lequel la touche est enfoncée
	*/
	int time_pressed(enum key k) const;

	/*!
	* 	@brief Accesseur 
	*	@return Vrai si une touche gauche ou droite est enfoncée
	*/
	bool key_dir_down() const;

	/*!
	* 	@brief Force le relachement de la touche 
	*	@param k la touche à relacher
	*/
	void disable_key(enum key k);
	
	/*!
	* 	@brief Force le relachement de toutes les touches
	*/
	void disable_all_keys();

};



#endif
