/**
 * 	@file events_manager.h
 * 	@brief header de la classe Events_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _EVENTS_MANAGER_
#define _EVENTS_MANAGER_

#include <list>

class Event;
class Trigger;
class Game_engine;
class Static_data;
class Camera;
class Pictures_container;
class Analyser;


/**
 * 	@class Events_manager
 * 	@brief Classe gérant l'ensemble des événements
 *
 *	- Contient l'ensembe des événements
 *	- Est chargé de les mettre à jour
 *	- Est chargé de déclencher leur affichage
 *	- Est chargé de les déclencher, de les détruire quand il le faut
 */
class Events_manager {
private:
	std::list<Event*> m_list_events;
	std::list<Trigger*> m_list_triggers;

	Game_engine *m_game_engine;
	Static_data *m_static_data;
	Pictures_container *m_pictures_container;
public:

	/**
	 * 	@brief Constructeur
	*/
	Events_manager();

	/**
	 * 	@brief Destructeur
	*/
	~Events_manager();

	/**
	 * 	@brief Initialise les paramètres de la classe
	 * 	@warning Ne charge pas les events!
	 *	@param static_data les données du niveau
	 *	@param game_engine le moteur de jeu
	 *	@param pictures_container Le conteneur d'images
	 *
	*/
	void init_events_manager(Static_data *static_data, Game_engine *game_engine, Pictures_container *pictures_container);

	/**
	 * 	@brief charge les events du niveau
	 *	@param analyser un Analyser ouvert sur le fichier level à charger
	*/
	void load_events(Analyser *analyser);

	/**
	 * 	@brief Met à jour l'ensemble des événements
	 *
	 *	Cette méthode détruit notamment les événements
	 *	à détruire
	*/
	void update();

	/**
	 * 	@brief Affiche à l'écran les événements affichables
	 *	@param camera La camera pour afficher les événements
	*/
	void display_events(Camera const * camera);

};

#endif
