/**
 * 	@file SoundEngine.h
 * 	@brief Header de la classe SoundEngine
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SOUND_ENGINE_
#define _SOUND_ENGINE_

#include "../lib/fmodapi375win/api/inc/fmod.h"

#include <string>
#include <map>
#include <list>
#include "items/Weapon.h"

#define MUSIC_CANAL 1
#define BABAR_FIRE_CANAL 2

#include <SFML/Audio.hpp>

class Sound;
class Sonorisable;
/**
 * 	@class SoundEngine
 * 	@brief Moteur de son
 *
 *
 */
class SoundEngine
{
private:
    std::map<std::string, sf::SoundBuffer*> m_soundBuffers;
    sf::Music *m_music;
    int m_sounds_volume;
    int m_music_volume;
    std::list<sf::Sound *> m_soundsPlaying;

public:

    /**
     * @brief Constructeur
    */
    SoundEngine();

    /**
     * @brief Destructeur
    */
    ~SoundEngine();

    void init_level (std::string level);

    /*!
    *	@brief Mise a jour des sons, doit etre appelee a chaque tour
    */
    void update();

    /**
    *	@brief Charge la musique a jouer
    *	@param str Le nom de la musique (avec l'extension, depuis le repertoire des musiques)
    */
    void load_music (std::string str);

    /**
     * @brief Joue la musique
    */
    void play_music();

    /**
     * @brief Joue la musique
    */
    void play_sound (std::string key);

    void play_sound (Sonorisable *sonorisable);

    void set_sounds_volume (int v);
    void set_music_volume (int v);
    int get_sounds_volume() const;
    int get_music_volume() const;
};


#endif
