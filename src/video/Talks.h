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

#include "../video/Camera.h"

#define PIC_TALKS_DIR "/pic/talks/"
#define FONTS_TALKS_DIR "/data/talks/fonts/"

#define POSX 15
#define POSW 770
#define POSH 30
#define POSY 450
#define LINES_NUMBER 4
#define DISPLAY_SPEED 20


#include "../video/font.h"
#include "../video/SurfaceText.h"
#include "../video/SpecialLetter.h"
#include "../video/surface.h"



struct cell_string {
	std::string str;
	std::string talker;
};

struct word_and_length {
	int length;
	std::list <SpecialLetter *> letters;
	bool newline;
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
	std::list<SpecialLetter *> m_text_surface[LINES_NUMBER]; // les lignes de textes a afficher
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
	bool m_have_to_leave; // vrai si le jeu doit etre quitte
	std::queue < std::queue < SpecialLetter * > > m_cell_letters;

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
	 *	@param PicturesContainer Le gestionnaire de chargement d'image
	 */
	void init_talks(Camera *camera, PicturesContainer *PicturesContainer);

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
	 *	@brief Indique si l'utilisateur veut quitter le jeu
	 *	@return Vrai si l'utilisateur veut quitter le jeu
	*/
	bool have_to_leave() const {return m_have_to_leave;}

	/**
	 *	@brief Affichage a l'ecran du dialogue
	*/
	void display();

	/*!
	*	@brief Coupe le texte et le stocke dans la liste de celllules
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

	/*!
	* 	@brief Mise a jour de la taille des lettres
	*/
	void update_letters();

	/*!
	*	@brief Convertit une chaine (dialogue) en liste de chaines (mots)
	*	@param str La chaine correspondant aux paroles d'un personnage
	*	@return La liste de mots
	*/
	static std::list< std::string > string_to_list_words(std::string str);

	static std::list< word_and_length > words_to_words_and_length(std::list < std::string > words);

	void prepare_cell_string(cell_string cell);

	static void treat_special_words(std::string specialword, std::list < word_and_length > &words_list);

	static std::list<std::string> convert_special_word(std::string specialword);
};







#endif
