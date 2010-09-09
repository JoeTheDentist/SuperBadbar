#ifndef _TALKS_
#define _TALKS_

#include <string>
#include <SDL/SDL_ttf.h>



#define PIC_TALKS_DIR "../pic/talks/"
#define FONTS_TALKS_DIR "../data/talks/fonts/"
#define TEXT_TALKS_DIR "../data/talks/texts/"



#define POSX 15
#define POSW 770
#define POSH 50
#define POSY 400
#define LINES_NUMBER 3
#define DISPLAY_SPEED 20

                          
struct cell_string {
	std::string str;
	cell_string *next;
};

class Talks {
private:
	SDL_Surface *m_text_background;
	SDL_Surface *m_text_surface[LINES_NUMBER];  
	SDL_Rect m_pos_background;
	SDL_Rect m_pos_text[LINES_NUMBER];
	TTF_Font *m_font;
	SDL_Color m_font_color;

public:
	Talks();
	~Talks();
	void display_background();
	struct cell_string *cut_text(std::string text);
	void instant_display(std::string str, int line);
	void progressive_display(std::string str, int line);
	void move_up();
	void display_line(int line);
	void wait_space();
	void display_text(std::string str);
	void load_and_display_text(std::string filename);

};







#endif