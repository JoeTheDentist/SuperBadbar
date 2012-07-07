/**
 * 	@file EventsManager.h
 * 	@brief header de la classe EventsManager
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _EventsManager_
#define _EventsManager_

#include <list>
#include <string>

class Event;
class Trigger;
class GameEngine;
class StaticData;
class Camera;
class PicturesContainer;
class Analyser;


/**
 * 	@class EventsManager
 * 	@brief Classe gérant l'ensemble des événements
 *
 *	- Contient l'ensembe des événements
 *	- Est chargé de les mettre �  jour
 *	- Est chargé de déclencher leur affichage
 *	- Est chargé de les déclencher, de les détruire quand il le faut
 */
class EventsManager {
private:
	std::list<Event*> m_list_events;
	std::list<Trigger*> m_list_triggers;

	GameEngine *m_GameEngine;
	StaticData *m_StaticData;
	std::string m_level_name;
public:

	/**
	 * 	@brief Constructeur
	*/
	EventsManager();

	/**
	 * 	@brief Destructeur
	*/
	~EventsManager();

	/**
	 * 	@brief Initialise les paramètres de la classe
	 * 	@warning Ne charge pas les events!
	 *	@param StaticData les données du niveau
	 *	@param GameEngine le moteur de jeu
	 *
	*/
	void init_EventsManager(StaticData *StaticData, GameEngine *GameEngine);

	/**
	 * 	@brief charge les events du niveau
	 *	@param analyser un Analyser ouvert sur le fichier level �  charger
	*/
	void load_events(Analyser *analyser);

	/**
	 * 	@brief charge les triggers du niveau
	 *	@param analyser un Analyser ouvert sur le fichier level �  charger
	*/
	void load_triggers(Analyser *analyser);

	/**
	 * 	@brief Met �  jour l'ensemble des événements
	 *
	 *	Cette méthode détruit notamment les événements
	 *	�  détruire
	*/
	void update();

	/**
	 * 	@brief Affiche �  l'écran les événements affichables
	 *	@param camera La camera pour afficher les événements
	*/
	void display_events(Camera const * camera);

        /**
         *  @brief Ajout de fin d'un niveau
         *  @param x : Absisses fin
         *  @param y : Ordonnees fin
         */
	void add_end_level(int x, int y);

};

#endif
