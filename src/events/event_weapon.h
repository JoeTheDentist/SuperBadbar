/**
 * 	@file event_weapon.h
 * 	@brief header de la classe Event_weapon
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _EVENT_WEAPON_
#define _EVENT_WEAPON_

#include "../events/events.h"
#include "../events/event_item.h"
#include "../items/weapons.h"
#include <SDL/SDL.h>

class Pictures_container;
class Babar;
class Weapon;
class Analyser;

/**
 * 	@class Event_weapon
 * 	@brief Événement correspondant à une arme à rammasser
 *	
 *	Quand la cible passe sur l'événement, elle obtient l'arme
 *	et l'événement est détruit
 *
 *	@todo Adapter la classe pour avoir n'importe quelle arme
 */
class Event_weapon: public Event_item{
private:
	weapon_type m_weapon_type;
public:
	
	/**
	 * 	@brief Constructeur
	 *	@param target Le Babar cible
	 *	@param pictures_container L'utilitaire pour charger les images
	 *	@param pos La position de départ de l'arme dans le niveau
	*/
	Event_weapon(Babar *target,Pictures_container *pictures_container, Rect pos);

	/**
	 * 	@brief Constructeur
	 *	@param target Le Babar cible
	 *	@param pictures_container L'utilitaire pour charger les images
	 * 	@param analyser Un pointeur vers un analyser ouvert sur le fichier level en cours
	 *
	 * 	Le constructeur lit la chaine et les deux int suivant le curseur de l'analyser, et 
	 *  s'arrete de parcourir le fichier. L'analyser est laissé ouvert et n'est pas parcouru 
	 * 	plus que nécessaire
	 *
	*/
	Event_weapon(Babar *target, Pictures_container *pictures_container, Analyser *analyser);

	/**
	 * 	@brief Destructeur
	*/
	~Event_weapon();

	/**
	 * 	@brief Déclenche l'événement
	 *
	 *	Donne à la cible l'arme en question et prépare
	 * 	l'événement à etre détruit
	*/
	void start();
	
	/**
	 * 	@brief Accesseur
	 *	@return L'image actuelle de l'événement
	*/
	SDL_Surface *current_picture() const;
};


#endif
