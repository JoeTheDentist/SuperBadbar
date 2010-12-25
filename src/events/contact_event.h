/**
 * 	@file contact_event.h
 * 	@brief header de la classe Contact_event
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _CONTACT_EVENT_
#define _CONTACT_EVENT_

#include "../events/events.h"
#include "../util/globals.h"



/**
 * 	@class Contact_event
 * 	@brief Evenement qui se déclenche au contact de Babar
 *
 *	Il se déclenche lorsque le Babar cible entre en contact
 *	avec sa surface. Il est alors déclenché et détruit.
 *
 *	@todo Rendre la classe abstraite\n
 *	Rendre le code adaptable à une liste de personnages
 */
class Babar;
class Surface;

class Contact_event: public Event{
protected:
	Babar *m_target;
	Surface *m_picture;
	Rect m_pos;
	int m_phase;
public:


/**
 * 	@brief Constructeur
 */
	Contact_event();

/**
 * 	@brief Constructeur
 *	@param target Le babar cible
 *	@param pos La position de l'objet
 */
	Contact_event(Babar *target, Rect pos);

/**
 * 	@brief Destructeur
 */
	virtual ~Contact_event();

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
	virtual Surface *current_picture() const;
	
/**
 * 	@brief Accesseur
 *	@return La position et le cadre de l'événement
 */
	virtual Rect current_pos() const;
};

#endif
