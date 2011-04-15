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

#include <list>
#include <string>
#include "../video/surface.h"
#include "../events/events.h"

class Analyser;

/**
 * 	@class Trigger
 * 	@brief Ensemble d'evenements declenchables lorsqu'on entre dans une zone
 *
 * Il n'est pas affichable
 *
 *	Format dans un .lvl:
 *	#Triggers#
 *	<nombre de triggers>
 *	chemin du trigger depuis le repertoire des levels 
 *	(en general: <nomlevel>triggers/fichiertrigger.trg)
 *	!
 *
 *	Format d'un .trg:
 *	#zone#
 *	<nombre de positions>
 *	x y w h
 *	!
 *	#events#
 *	<nombre d'events>
 *	"event" eventype x y
 *
 */
class Trigger {
protected:
	std::list<Rect> m_zone;
	std::list<Event *> m_events;
	bool m_triggered;
public:
	
	/**
	 * 	@brief Constructeur
	 *	@param filename Le chemin vers le fichier trigger depuis le repertoire des niveaux
	*/
	Trigger(std::string filename);

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
	
	/*!
	 *	@brief Ajoute une position a la zone de declenchement
	 *	@param pos La position a ajouter
	 */
	void addPos(Rect pos);
	
	/*!
	 *	@brief Ajoute un evenement a la liste des evenements a declencher
	 *	@param event L'evenement a ajouter
	 */
	void addEvent(Event *event);
	

};


#endif
