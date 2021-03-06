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


#include <string>

#include "util/utils.h"

#include <SFML/Window.hpp>

class EventKeyboard;


/*!
*	@class KeyboardConfig
*	@brief Configuration du clavier
*/
class KeyboardConfig
{
private:
    enum key m_key_config[sf::Key::Count];	// tableau de configuration des touches

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
    void loadConfig (std::string config_name);

    /*!
    * 	@brief Sauvegarde La configuration des touches dans un fichier
    *	@param config_name Le nom du fichier de configuration depuis le dossier des fichiers de configuration
    */
    void saveConfig (std::string config_name);

    /*!
    *	@brief Change la configuration de la touche k pour sdl_code
    *	@param k La touche a modifier
    *	@param sdl_code Le code string sdl de la nouvelle touche (cf SfmlKeyConvertor)
    *	@param save True if we want to save the configuration
    */
    void setConfigKey (key k, std::string sdl_code, bool save = true);

    /*!
    *	@brief Renvoie le code string sdl de la touche correspondant a k
    *	@param k La touche dont on veut l'info
    *	@return le code string sdl de la touche correspondant a k
    */
    std::string getStringKey (key k);

    /*!
    *	@brief Accesseur
    *	@param Une touche au format SDL
    *	@return L'enum key correspondant (k_none s'il n'y en a pas)
    */
//~ 	key getEnumKey(SDLKey key) const;
    key getEnumKey (sf::Key::Code key) const;

    /*!
    *	@brief Accesseur
    *	@param Une touche au format EventKeyboard
    *	@return L'enum key correspondant (k_none s'il n'y en a pas)
    */
    key getEnumKey (const EventKeyboard &eventKeyboard) const;
};

#endif
