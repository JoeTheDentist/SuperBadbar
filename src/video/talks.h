/**
 * 	@file talks.h
 * 	@brief Header de la classe Talks
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _TALKS_
#define _TALKS_

#include <string>


#include "../video/camera.h"

#define PIC_TALKS_DIR "/pic/talks/"
#define FONTS_TALKS_DIR "/data/talks/fonts/"



#define POSX 15
#define POSW 770
#define POSH 30
#define POSY 410
#define LINES_NUMBER 4
#define DISPLAY_SPEED 20


#include "../video/font.h"
#include "../video/surface_text.h"
#include "../video/surface.h"

struct cell_string {
	std::string str;
	cell_string *next;
};



/**
 * 	@class Talks
 * 	@brief Gestionnaire graphique de dialogues
 */
class Talks {
private:
	Surface *m_text_background;
	Surface *m_talker;
	std::list<Surface_text *> m_text_surface[LINES_NUMBER];
	Rect m_pos_background;
	Rect m_pos_talker;
	Rect m_pos_text[LINES_NUMBER];
	int m_curr_line;
	unsigned int m_string_curs;
	Font m_font;
	Camera *m_camera;
	bool m_active;
	std::string m_text;
	bool m_waiting_for_enter;


	void display_background();
	void move_up();
	void end_move_up();
	void clear_talks();
public:
	/**
	 * 	@brief Constructeur
	 */
	Talks();

	/**
	 * 	@brief Destructeur
	 */
	~Talks();

	/**
	 * 	@brief Initialisation des paramètres de l'objet
	 *	@param camera Le gestionnaire d'affichage
	 *	@param pictures_container Le gestionnaire de chargement d'image
	 */
	void init_talks(Camera *camera, Pictures_container *pictures_container);

	/**
	 * 	@brief Affiche sous forme de dialogue la chaine de caractères
	 *	@param str Chaine à afficher
	 *	@warning A faire suivre par un keyboard.disable_all_keys(); pour éviter des effets indésirables
	 *	dus à la configuration du clavier avant l'appel
	 */
	void display_text(std::string str);

	/**
	 * 	@brief Affiche sous forme de dialogue le contenu du fichier
	 *	@param filename Chemin du fichier à afficher
	 *	@warning A faire suivre par un keyboard.disable_all_keys(); pour éviter des effets indésirables
	 *	dus à la configuration du clavier avant l'appel
	 */
	void load_and_display_text(std::string filename);
	
	/**
	 *	@brief Mise a jour de talks
	*/
	void update();
	
	/**
	 *	@brief Indique si la fenetre est active
	 *	@return Vrai si la fenetre est active
	*/
	bool isActive();
	
	/**
	 *	@brief Affichage a l'ecran du dialogue
	*/	
	void display();
	
	/*!
	*	@brief Rajoute une lettre au texte affiche, sauf s'il faut move_up
	*	@return Vrai s'il faut move_up
	*/
	bool write_letter();
	
	/*!
	*	@brief Retourne vrai si on a fini d'afficher le texte
	*	@return vrai si on a fini d'afficher le texte
	*/
	bool end_of_text();

};







#endif
