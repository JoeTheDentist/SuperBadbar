/**
 * 	@file Event.h
 * 	@brief header de la classe Event
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _EVENTS_
#define _EVENTS_

#include <string>
#include "../video/surface.h"

class Analyser;

/**
 * 	@class Event
 * 	@brief Classe representant un evenement declenchable
 *
 *	Un event possede une methode pour savoir s'il doit etre declenche (can_start)
 * 	et une autre pour etre declenche (start)
 *	Il peut etre détruit quand il est devenu inutile et est affichable
 *
 *
 */
class Event {
protected:
	bool m_can_be_destroyed;
	Surface *m_picture;
	Rect m_pos;
	int m_phase;
	Analyser *m_analyser;
	std::string m_event_name;

public:

	/**
	 * 	@brief Constructeur
	*/
	Event(std::string event_name, int x, int y);

	/**
	 * 	@brief Destructeur
	*/
	virtual ~Event();

	/**
	 * 	@brief Mise à jour des données de l'Event
	*/
	virtual void update();

	/**
	 * 	@brief Indique si l'événement doit etre déclenché
	 *	@return Vrai si l'événement doit etre déclenché
	*/
	virtual bool can_start() const;

	/**
	 * 	@brief Déclenche l'événement
	*/
	virtual void start();

	/**
	 * 	@brief Indique si l'événement doit etre détruit
	 *	@return Vrai si l'événement doit etre détruit
	*/
	virtual bool can_be_destroyed() const;

	/**
	 * 	@brief Détruit l'événement
	*/
	virtual void destroy();

	/**
	 * 	@brief Accesseur
	 *	@return L'image actuelle de l'événement
	*/
	virtual Surface *current_picture() const;

	/**
	 * 	@brief Accesseur
	 *	@return La position actuelle de l'événement
	*/
	virtual Rect current_pos() const;

protected:
	// ramassage d'une arme
	void process_weapon();
	// point de vie
	void process_HPup();
	// jeu d'un son
	void process_playsound();
	// victoire (du niveau)
	void process_victory();
	// ramassage d'une cacahuete
	void process_peanut();
	// jeu d'un dialogue
	void process_dialog();
	// ajout d'un monstre
	void process_monster();
};


#endif
