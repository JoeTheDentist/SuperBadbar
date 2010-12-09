/**
 * Classe Camera: classe singleton qui gère toute la partie graphique du jeu.
 * Elle initialise la SDL, ouvre la fenetre et les ferme.
 * Elle pointe sur un sprite qu'elle suit dans ses déplacements avec update_pos(), appelé par la classe Game.
 * Elle permet d'afficher des sprites et le fond d'écran aux bons endroits en calculant leur position relative
 * à la fenetre à partir de leur position absolue.
 * Elle permet aussi d'afficher une Surface * quelconque à une position donnée dans la fenetre (indépendamment
 * de la position de la camera)
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

class Camera {
private:
	SDL_Rect m_frame;		/* cadre de la camera */
	SDL_Rect m_direction; 	/* direction de la camera (les composantes sont à valeur dans {-1, 1}*/
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
	void display_background(SDL_Surface *background); 

	/*!
	* 	@brief Affiche le sprite passé en paramètre à l'écran
	*	@param sprite le sprite à afficher
	*
	*	Le sprite est affiché en fonction de sa position 
	*	relativement à la position de la caméra
	*	Si le sprite vaut NULL, rien ne se passe
	*/
	void display_sprite(Sprite *sprite);
	
	/*!
	* 	@brief Affiche le Static passé en paramètre à l'écran
	*	@param sttc le Static à afficher
	*	Le Static est affiché en fonction de sa position 
	*	relativement à la position de la caméra
	*	Si le Static vaut NULL, rien ne se passe	
	*/
	void display_static(Static *sttc);
	
	/*!
	* 	@brief Affiche les événements affichables de l'event_manager
	*	@param event_manager l'ensemble des événements à afficher
	*/
	void display_events(Events_manager *event_manager);
	
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
	Rect frame();
	
	/*!
	* 	@brief Affiche pic à la position pos par rapport au cadre de la camera
	*	@param pic L'image à afficher
	*	@param pos la position de l'image (relativement au cadre de la camera!!)
	*/
	void display_picture(SDL_Surface *pic, Rect *pos); 
	
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
