/**
 * 	@file trigger.h
 * 	@brief header de la classe Trigger
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _TRIGGER_
#define _TRIGGER_

#include <string>
#include "../video/surface.h"
#include <list>
#include "../events/events.h"

class Analyser;

/**
 * 	@class Trigger
 * 	@brief Ensemble d'evenements declenchables lorsqu'on entre dans une zone
 *
 * Il n'est pas affichable
 *
 */
class Trigger {
protected:
	bool m_can_be_destroyed;
	std::list<Rect> m_zone;
	std::list<Event *> m_events;
public:
	
	/**
	 * 	@brief Constructeur
	*/
	Trigger();

	/**
	 * 	@brief Destructeur
	*/
	virtual ~Trigger();

	/**
	 * 	@brief Mise à jour des données de l'Trigger
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
	

};


#endif
