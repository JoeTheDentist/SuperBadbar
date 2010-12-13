/**
 * 	@file event_item.h
 * 	@brief header de la classe Event_item
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _EVENT_ITEM_
#define _EVENT_ITEM_

#include "../events/events.h"
#include "../util/globals.h"



/**
 * 	@class Event_item
 * 	@brief Evenement correspondant à un objet ramassable
 *
 *	Il se déclenche lorsque le Babar cible entre en contact
 *	avec sa surface. Il est alors déclenché et détruit.
 *
 *	@todo Rendre la classe abstraite\n
 *	Rendre le code adaptable à une liste de personnages
 */
class Babar;

class Event_item: public Event{
protected:
	Babar *m_target;
	SDL_Surface *m_picture;
	Rect m_pos;
	int m_phase;
public:

/**
 * 	@brief Constructeur
 *	@param target Le babar susceptible de ramasser l'item
 *	@param pos La position de l'objet
 */
	Event_item(Babar *target, Rect pos);

/**
 * 	@brief Destructeur
 */
	~Event_item();

/**
 * 	@brief Mise à jour de l'événement
 *
 *	Modifie la position de l'événement pour le faire
 *	osciller de bas en haut
 */
	virtual void update();

/**
 * 	@brief Retourne vrai si l'événement doit etre déclenché
 *	@return Vrai si l'événement doit etre déclenché
 *
 *	L'événement doit etre déclenché si la cible entre en contact
 *	avec l'événement 
 */
	virtual bool can_start() const;
	
/**
 * 	@brief Déclenche l'événement
 *
 *	Par défaut, rend l'événement déstruisible
 */
	virtual void start();
	
/**
 * 	@brief Accesseur
 *	@return L'image actuelle de l'event
 *
 *	S'il n'y a pas d'image, retourne NULL
 */
	virtual SDL_Surface *current_picture() const;
	
/**
 * 	@brief Accesseur
 *	@return La position et le cadre de l'événement
 */
	virtual Rect current_pos() const;
};

#endif
