/**
 * 	@file KeyboardConfig.h
 * 	@brief header de la Classe KeyboardConfig
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */
 
 
#ifndef _KEYBOARD_CONFIG_H_
#define _KEYBOARD_CONFIG_H_

#include "../util/utils.h"
#include <string>
#include "../../lib/SDL/include/SDL/SDL.h"


/*!
*	@class KeyboardConfig
*	@brief Configuration du clavier
*/
class KeyboardConfig {
private:
	enum key m_key_config[SDLK_LAST];	// tableau de configuration des touches

public:
	/*!
	*	@brief Constructeur
	*/
	KeyboardConfig();

	/*!
	*	@brief Destructeur
	*/
	~KeyboardConfig() {}
		
	/*!
	* 	@brief Charge La configuration des touches depuis un fichier
	*	@param config_name Le nom du fichier de configuration depuis le dossier des fichiers de configuration
	*/
	void loadConfig(std::string config_name);
		
	/*!
	* 	@brief Sauvegarde La configuration des touches dans un fichier
	*	@param config_name Le nom du fichier de configuration depuis le dossier des fichiers de configuration
	*/
	void saveConfig(std::string config_name);

	/*!
	*	@brief Change la configuration de la touche k pour sdl_code
	*	@param k La touche a modifier
	*	@param sdl_code Le code string sdl de la nouvelle touche (cf SdlKeyConverter)
	*	@param save True if we want to save the configuration
	*/
	void setConfigKey(key k, std::string sdl_code, bool save = true);
	
	/*!
	*	@brief Renvoie le code string sdl de la touche correspondant a k
	*	@param k La touche dont on veut l'info
	*	@return le code string sdl de la touche correspondant a k
	*/
	std::string getStringKey(key k);
	
	/*!
	*	@brief Accesseur
	*	@param Une touche au format SDL
	*	@return L'enum key correspondant (k_none s'il n'y en a pas)
	*/
	key getKey(SDLKey key) {return m_key_config[int(key)];}
};

#endif
