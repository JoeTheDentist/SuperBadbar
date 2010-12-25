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

#include "../events/contact_event.h"
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

class Event_item: public Contact_event {
protected:
public:

/*!
 *	@brief Constructeur par défaut
 */
	Event_item();

/*!
 * 	@brief Constructeur
 *	@param target Le babar susceptible de ramasser l'item
 *	@param pos La position de l'objet
 */
	Event_item(Babar *target, Rect pos);

/*!
 * 	@brief Destructeur
 */
	virtual ~Event_item();


};

#endif
