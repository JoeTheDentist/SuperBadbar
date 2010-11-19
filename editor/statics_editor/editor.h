#ifndef _EDITOR_
#define _EDITOR_

#define NO_COLL 0x0
#define FULL_COLL 0xF
#define DOWN_COLL 0x4
#define CLIMB_COLL 0x10

#define SQUARE_SIZE 5

#define STATICS_DIR "../../pic/statics/"
#define COLL_EXT ".col"
#define PICS_EXT ".bmp"
#define EDITOR_PIC_DIR "../../../pic/editor/"

#include "statics.h"
#include "windows.h"

class Editor {
private:
	Window m_window;			/* fenetre de jeu */
	Static m_static;			/* static à modifier */
	uint32_t m_curr_coll;		/* carré de collision à blitter */
	bool m_leave;				/* booléen pour quitter */
public:
	Editor(std::string static_name);		/* constructeur à partir du nom du static à éditer */
	~Editor();								/* destructeur */
	void edit();							/* fonction principale d'édition */
	void switch_coll();						/* changer de carré à blitter (m_curr_coll) */
	void right_clic(uint32_t x, uint32_t y);/* traitement du clic droit */
	void left_clic(uint32_t x, uint32_t y);	/* traitement du clic gauche */
	void save();							/* sauvegarde du static */
	void refresh_screen();					/* raffraichit l'affichage */
	void write_square(uint32_t x, uint32_t y); /* met à jour la case cliquée avec m_curr_coll et l'affiche */
	void draw_ligne(float x, float y, float X, float Y); /* affiche une ligne de carrés de type m_coll_type */
	void draw_square(uint32_t x, uint32_t y); /* affiche un carrés de type m_coll_type */
	void write_ligne(float x, float y, float X, float Y); /* trace une ligne de carrés de type m_coll_type */
	void refresh_ligne(float x, float y, float X, float Y); /* rafraichit l'affichage de la ligne de carrés sélectionnée avec les données du static */
	void refresh_square(uint32_t x, uint32_t y); /* rafraichit l'affichage du carré sélectionnée avec les données du static */

	void leave();							/* quitte l'éditeur */
};


#endif
