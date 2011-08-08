/**
 * 	@file Camera.h
 * 	@brief Header de la classe Camera
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


/**
 * 	@class Camera
 * 	@brief Gestionnaire d'affichage
 *
 *
 * Initialise la SDL, ouvre la fenetre et les ferme.\n
 * Pointe sur un sprite qu'elle suit dans ses déplacements avec update_pos().\n
 * Permet d'afficher des sprites et le fond d'écran aux bons endroits en calculant leur position relative
 * a la fenetre a partir de leur position absolue.\n
 * Permet aussi d'afficher une Surface * quelconque a une position donnée dans la fenetre (indépendamment
 * de la position de la camera)\n
 * La camera suit le sprite pointé sauf lorsqu'il arrive aux limites du niveau.
**/

#ifndef _CAMERA_
#define _CAMERA_


#include <SDL/SDL.h>
#include <SFML/Window.hpp>

#include "util/globals.h"
#include "util/debug.h"

#define VITESSE_DECALAGE_CAMERA 25
#define VITESSE_DECALAGE_RETOUR_CAMERA 10
#define MAX_DECALAGE_CAMERA 0.15

class Actor;
class Babar;
class Monster;
class Projectile;
class Static;
class StaticData;
class EventsManager;
class Event;
class Surface;
class MovingPlatform;
class Displayable;

class Camera {
private:
	sf::RenderWindow *m_window;
	Rect m_frame;		/* cadre de la camera */
	Rect m_direction; 	/* direction de la camera (les composantes sont a valeur dans {-1, 1}*/
	Rect m_decalage; 	/* decalage du cadre (en fonction de la direction regardée) */
	Actor *m_target;		/* sprite sur lequel pointe la camera */
	SDL_Surface *m_screen;
	Surface *m_green_coll;
	Surface *m_red_coll;
	bool m_initialized;
public:

	/**
	*	@brief Constructeur par défaut
	*/
	Camera();

	/**
	* 	@brief Destructeur
	*/
	~Camera();

	/**
	* 	@brief Fait pointer la camera sur le sprite passé en paramètre et crée la fenetre SDL
	* 	@param target Le sprite a pointer
	*/
	void init_camera(Actor *target);

 	/**
	* 	@brief Fait pointer la camera sur le sprite passé en paramètre
	* 	@param target Le sprite a pointer
	*/
	void set_target(Actor *target);

	/**
	* 	@brief Met a jour la position de la camera
	*	@param StaticData fournit la taille de l'écran
	* 	@warning Il va falloir virer ce fucking StaticData
	*
	*	Suit la position de babar, sans acoups, en s'arretant aux bords du niveau
	*	et en étant décalé dans la direction du regard de babar.
	*/
	void update_pos();

	/**
	* 	@brief Affiche le fond d'écran passé en paramètre
	*	@param background l'image du fond d'écran
	*/
	void display_background(Surface *background) ;

	/**
	* 	@brief Affiche le Displayable passé en paramètre a l'écran
	*	@param entity le Displayable a afficher
	*	Le Displayable est affiché en fonction de sa position
	*	relativement a la position de la caméra
	*	Si le Displayable vaut NULL, rien ne se passe
	*	@todo N'utiliser que cette méthode
	*/
	void display(Displayable * const entity) const;

	/**
	* 	@brief Affiche les événements affichables de l'event_manager
	*	@param event_manager l'ensemble des événements a afficher
	*/
	void display_events(EventsManager * const event_manager) const;

	/**
	* 	@brief Affiche l'événement s'il est affichable en fonction
	*	de sa position et de son image
	*	@param event l'événement a afficher
	*/
	void display_event(Event *event) const;

	/**
	* 	@brief Accesseur
	*	@return La position et le cadre de la caméra
	*/
	Rect frame() const;

	int width() const;

	int height() const;

	/**
	* 	@brief Affiche pic a la position pos par rapport au cadre de la camera
	*	@param surf L'image a afficher
	*	@param pos la position de l'image (relativement au cadre de la camera!!)
	*	@todo Supprimer la surcharge. Le probleme vient de la création d'images par TTF qu'il faut encapsuler
	*/
	void display_picture(Surface *surf, Rect *pos, bool fixe=false) const;
//~ 	void display_picture(SDL_Surface *surf, Rect *pos) ; /*je ne suis pas arrivé a la rendre const...*/

	/**
	*	@brief Met a jour l'affichage de la caméra
	*
	*	L'affichage réel n'est mis a jour que dans cette méthode
	*/
	void flip_camera();

	/**
	*	@brief Accesseur
	*	@return La surface SDL de l'ecran
	*/
	SDL_Surface *sdl_screen() { return m_screen; }
	
	sf::Window *getWindow() const {return m_window;}


	#ifdef DEBUG_COLL
	void display_green_coll(Rect pos);
	void display_red_coll(Rect pos);
	#endif

private:
	void update_decalage();	/* mise a jour du decalage du cadre (appelé par update_pos) */
};



#endif
