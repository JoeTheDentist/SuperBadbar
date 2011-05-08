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
#include "../events/triggerable.h"

class Analyser;

/**
 * 	@class Trigger
 * 	@brief Ensemble d'triggerables declenchables lorsqu'on entre dans une zone
 *
 * Il n'est pas affichable
 *
 *	Format dans un .lvl:
 *	#Triggers#
 *	<nombre de triggers>
 *	numeros des trigger
 *	!
 *
 *	Format d'un .trg:
 *	#zone#
 *	<nombre de positions>
 *	x y w h
 *	!
 *	#triggerables#
 *	<nombre de riggerables>
 *	<TRIGGERABLE>  (utiliser la syntaxe definie dans triggerable)
 *
 */
class Trigger {
protected:
	std::list<Rect> m_zone;
	std::list<Triggerable *> m_triggerables;
	bool m_triggered;
public:
	
	/**
	 * 	@brief Constructeur
	 *	@param level_number le numero du trigger
	 *	@param level_name le nom du niveau
	*/
	Trigger(int trigger_number, std::string level_name);

	/**
	 * 	@brief Destructeur
	*/
	virtual ~Trigger();

	/**
	 * 	@brief Mise à jour des données de l'Trigger
	*/
	virtual void update();

	/**
	 * 	@brief Indique si l'triggerable doit etre déclenché
	 *	@return Vrai si l'triggerable doit etre déclenché
	*/
	virtual bool can_start() const;
	
	/**
	 * 	@brief Déclenche le triggerable
	*/
	virtual void start();
	
	/**
	 * 	@brief Indique si le trigger doit etre détruit
	 *	@return Vrai si le trigger doit etre détruit
	*/
	virtual bool can_be_destroyed() const;
	
	/**
	 * 	@brief Détruit le triggerable
	*/
	virtual void destroy();
	
	/*!
	 *	@brief Ajoute une position a la zone de declenchement
	 *	@param pos La position a ajouter
	 */
	void addPos(Rect pos);
	
	/*!
	 *	@brief Ajoute un triggerable a la liste des triggerables a declencher
	 *	@param triggerable le triggerable a ajouter
	 */
	void addTriggerable(Triggerable *triggerable);
	

};


#endif
