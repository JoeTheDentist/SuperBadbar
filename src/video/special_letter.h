/**
 * 	@file special_letter.h
 * 	@brief Header de la classe Special_letter
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "../video/surface_text.h"
#include <string>

class Special_letter : public Surface_text {
private:
	char m_letter;
	int m_offset_size;
	int m_size;
	int m_r;
	int m_g;
	int m_b;
	std::string m_font_name;
public:
	Special_letter(char letter, int size = 30, int r = 255, int g = 255, int b = 255, std::string font_name = "defaultfont.ttf");
	~Special_letter();
	void update();
	virtual int fake_w();
	virtual int fake_h();
protected:
//~ 	virtual void init(std::string text, int size = 30, int r = 255, int g = 255, int b = 255, std::string font_name = "defaultfont.ttf");
	
	
};
