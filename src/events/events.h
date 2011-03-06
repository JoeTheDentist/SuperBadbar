/**
 * 	@file events.h
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
 * 	@brief Classe mère de tous les événements
 *
 *	Fournit les prototypes des méthodes de mise à jour,
 *	de déclenchenement, de destruction et les accesseurs
 *
 *	@todo Rendre la classe abstraite\n
 */
class Event {
protected:
	bool m_can_be_destroyed;
	Surface *m_picture;
	Rect m_pos;
	int m_phase;
	Analyser *m_analyser;

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
	void process_weapon();
	void process_lifeup();
	void process_playsound();
	void process_victory();
};


#endif
