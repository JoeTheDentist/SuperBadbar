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
#include <queue>

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
#include "../video/special_letter.h"
#include "../video/surface.h"

struct cell_string {
	std::string str;
	std::string talker;
};



/**
 * 	@class Talks
 * 	@brief Gestionnaire graphique de dialogues
 */
class Talks {
private:
	Surface *m_text_background; // le fond d'ecran du talks
	Surface *m_frame_background; // le fond d'ecran du talks
	Surface *m_talker;  // la surface du talker courant
	std::list<Special_letter *> m_text_surface[LINES_NUMBER]; // les lignes de textes a afficher
	std::queue<cell_string> m_cells; // les cellules a afficher
	Rect m_pos_background; // la position du fond du talks 
	Rect m_pos_talker; // la position de l'image du talker
	Rect m_pos_text[LINES_NUMBER]; // les positions des lignes de text
	int m_curr_line; // le numero de ligne courante (par rapport au move_up)
	unsigned int m_string_curs; // le curseur dans m_text
	Font m_font; // police utilisee pour l'affichage
	Camera *m_camera; // wtf
	bool m_active; // vrai si le talks doit etre affiche
	std::string m_text; // la replique courante
	bool m_waiting_for_enter; // vrai si on doit attendre "entree" avant de continuer


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
	*	@brief Coupe le texte en parallele et le stocke dans la liste de celllules
	*	@param str Le texte a couper
	*/
	void aux_cut_text(std::string str);
	
	/*!
	*	@brief Lance l'affichage d'une cellule
	*	@param cell La cellule a afficher
	*/
	void aux_display_cell(cell_string cell);
	
	/*!
	*	@brief Indique si on a fini d'afficher la cellule courante
	*	@return Vrai si on a fini
	*/
	bool aux_end_of_cell();


	/**
	 *	@brief Affichage du background
	*/
	void display_background();

	/*!
	 *	@brief Fait remonter les lignes de dialogue 
	 *	
	 *	Si la boite est pleine, il faudra ensuite appuyer sur entrer pour que
	 *	end_move_up() soit appelé et finisse le move_up
	*/
	void move_up();

	/*!
	 *	@brief Finit le move_up si la boite de dialogue est pleine
	*/
	void end_move_up();

		/*!
	*	@brief Rajoute une lettre au texte affiche, sauf s'il faut move_up
	*	@return Vrai s'il faut move_up
	*/
	bool write_letter();
	
	/*!
	*	@brief Retourne vrai si on a fini l'affichage
	*	@return vrai si on a fini l'affichage
	*/
	bool end_of_talks();
	
	
	/*!
	*	@brief Vide les lignes de texte
	*/
	void clear_lines();
	
	void update_letters();

};







#endif
