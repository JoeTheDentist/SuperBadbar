/**
 * 	@file camera.h
 * 	@brief Header de la classe Camera
 *
 * 	@author Guillaume Bérard & Benoit Morel
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
 * à la fenetre à partir de leur position absolue.\n
 * Permet aussi d'afficher une Surface * quelconque à une position donnée dans la fenetre (indépendamment
 * de la position de la camera)\n
 * La camera suit le sprite pointé sauf lorsqu'il arrive aux limites du niveau.
**/

#ifndef _CAMERA_
#define _CAMERA_

#include "../util/globals.h"


#define VITESSE_DECALAGE_CAMERA 25
#define VITESSE_DECALAGE_RETOUR_CAMERA 10
#define MAX_DECALAGE_CAMERA 0.15

class Sprite;
class Babar;
class Monster;
class Projectile;
class Static;
class Static_data;
class Events_manager;
class Event;
class Surface;

class Camera {
private:
	Rect m_frame;		/* cadre de la camera */
	Rect m_direction; 	/* direction de la camera (les composantes sont à valeur dans {-1, 1}*/
	SDL_Rect m_decalage; 	/* decalage du cadre (en fonction de la direction regardée) */
	Sprite *m_target;		/* sprite sur lequel pointe la camera */
	SDL_Surface *m_screen;
public:

	/*!
	*	@brief Constructeur par défaut 
	*/
	Camera();			
	
	/*!
	* 	@brief Destructeur 
	*/
	~Camera();			

	/*!
	* 	@brief Fait pointer la camera sur le sprite passé en paramètre
	* 	@param target Le sprite à pointer
	*/
	void init_camera(Sprite *target);

	/*!
	* 	@brief Met à jour la position de la camera 
	*	@param static_data fournit la taille de l'écran
	* 	@warning Il va falloir virer ce fucking static_data
	*
	*	Suit la position de babar, sans acoups, en s'arretant aux bords du niveau
	*	et en étant décalé dans la direction du regard de babar.
	*/
	void update_pos(Static_data *static_data);						

	/*!
	* 	@brief Affiche le fond d'écran passé en paramètre 
	*	@param background l'image du fond d'écran
	*/
	void display_background(Surface *background) ; 

	/*!
	* 	@brief Affiche le sprite passé en paramètre à l'écran
	*	@param sprite le sprite à afficher
	*
	*	Le sprite est affiché en fonction de sa position 
	*	relativement à la position de la caméra
	*	Si le sprite vaut NULL, rien ne se passe
	*/
	void display_sprite(const Sprite * sprite) const;
	
	/*!
	* 	@brief Affiche le Static passé en paramètre à l'écran
	*	@param sttc le Static à afficher
	*	Le Static est affiché en fonction de sa position 
	*	relativement à la position de la caméra
	*	Si le Static vaut NULL, rien ne se passe	
	*/
	void display_static(Static *sttc) ;
	
	/*!
	* 	@brief Affiche les événements affichables de l'event_manager
	*	@param event_manager l'ensemble des événements à afficher
	*/
	void display_events(Events_manager * const event_manager) const;
	
	/*!
	* 	@brief Affiche l'événement s'il est affichable en fonction 
	*	de sa position et de son image
	*	@param event l'événement à afficher
	*/
	void display_event(Event *event);

	/*!
	* 	@brief Accesseur
	*	@return La position et le cadre de la caméra
	*/
	Rect frame() const;
	
	/*!
	* 	@brief Affiche pic à la position pos par rapport au cadre de la camera
	*	@param surf L'image à afficher
	*	@param pos la position de l'image (relativement au cadre de la camera!!)
	*	@todo Supprimer la surcharge. Le probleme vient de la création d'images par TTF qu'il faut encapsuler
	*/
	void display_picture(Surface *surf, Rect *pos) ; 
	void display_picture(SDL_Surface *surf, Rect *pos) ; 
	
	/*!
	*	@brief Met à jour l'affichage de la caméra
	*
	*	L'affichage réel n'est mis à jour que dans cette méthode
	*/
	void flip_camera();

private:
	void update_decalage();	/* mise à jour du decalage du cadre (appelé par update_pos) */
};



#endif
