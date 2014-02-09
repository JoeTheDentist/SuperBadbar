/**
 * 	@file KeyboardConfig.cpp
 * 	@brief implementation de la Classe KeyboardConfig
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#include "KeyboardConfig.h"

#include <fstream>
#include <iostream>

#include <control/EventKeyboard.h>
#include <control/SfmlKeyConvertor.h>


KeyboardConfig::KeyboardConfig()
{
    for (uint32_t i = 0; i < sf::Key::Count; i++)
        m_key_config[i] = k_none;
    m_key_config[sf::Key::Up] = k_up;
    m_key_config[sf::Key::Down] = k_down;
    m_key_config[sf::Key::Left] = k_left;
    m_key_config[sf::Key::Right] = k_right;
    m_key_config[sf::Key::Q] = k_jump;
    m_key_config[sf::Key::D] = k_fire;
    m_key_config[sf::Key::Escape] = k_escape;
    m_key_config[sf::Key::Space] = k_action;
    m_key_config[sf::Key::A] = k_prev_weapon;
    m_key_config[sf::Key::Z] = k_next_weapon;
//~ 	loadConfig("defaultkey.cfg");
    loadConfig ("customizekey.cfg");
}

void KeyboardConfig::loadConfig (std::string config_name)
{
#define LOCAL_LOAD_KEY(yop) \
    if (analyser.find_string(QUOTE_ACO(yop))) \
        setConfigKey(yop, SfmlKeyConvertor::sfmlkeyToStdstring(sf::Key::Code(analyser.read_int())), false);
    Analyser analyser;
    if (!analyser.open (CONFIG_R + config_name) )
        return;
    LOCAL_LOAD_KEY (k_up)
    LOCAL_LOAD_KEY (k_down)
    LOCAL_LOAD_KEY (k_left)
    LOCAL_LOAD_KEY (k_right)
    LOCAL_LOAD_KEY (k_jump)
    LOCAL_LOAD_KEY (k_fire)
    LOCAL_LOAD_KEY (k_escape)
    LOCAL_LOAD_KEY (k_prev_weapon)
    LOCAL_LOAD_KEY (k_next_weapon)
    LOCAL_LOAD_KEY (k_action)
    analyser.close();
}

void KeyboardConfig::saveConfig (std::string config_name)
{
    std::cout << "save dans " << CONFIG_R + config_name << std::endl;
    std::ofstream out ( (CONFIG_R + config_name).c_str(), std::ios::out | std::ios::trunc);
#define LOCAL_SAVE_KEY(yop) \
    out << "{" << #yop << "} " << SfmlKeyConvertor::stdstringToSfmlkey(getStringKey(yop)) << std::endl;
    LOCAL_SAVE_KEY (k_up)
    LOCAL_SAVE_KEY (k_down)
    LOCAL_SAVE_KEY (k_left)
    LOCAL_SAVE_KEY (k_right)
    LOCAL_SAVE_KEY (k_jump)
    LOCAL_SAVE_KEY (k_fire)
    LOCAL_SAVE_KEY (k_escape)
    LOCAL_SAVE_KEY (k_prev_weapon)
    LOCAL_SAVE_KEY (k_next_weapon)
    LOCAL_SAVE_KEY (k_action)
    out.close();
}

void KeyboardConfig::setConfigKey (key k, std::string sdl_code, bool save)
{
    sf::Key::Code new_sdlk = SfmlKeyConvertor::stdstringToSfmlkey (sdl_code);
    for (int i = 0; i <= (int) sf::Key::Count; ++i)
    {
        if (m_key_config[i] == k)
        {
            m_key_config[i] = k_none;
        }
    }
    m_key_config[new_sdlk] = k;
    if (save)
        saveConfig ("customizekey.cfg");

}

std::string KeyboardConfig::getStringKey (key k)
{
    for (int i = 0; i < (int) sf::Key::Count; ++i)
    {
        if (m_key_config[i] == k)
        {
            return SfmlKeyConvertor::sfmlkeyToStdstring ( (sf::Key::Code (i) ) );
        }
    }
    return "unknown";
}

key KeyboardConfig::getEnumKey (sf::Key::Code key) const
{
    return m_key_config[int (key)];
}

key KeyboardConfig::getEnumKey (const EventKeyboard &eventKeyboard) const
{
    return getEnumKey (eventKeyboard.getSFMLEvent().Key.Code);
}
