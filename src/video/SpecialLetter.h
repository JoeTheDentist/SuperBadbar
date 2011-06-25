/**
 * 	@file SpecialLetter.h
 * 	@brief Header de la classe SpecialLetter
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "../video/SurfaceText.h"
#include <string>

class SpecialLetter : public SurfaceText {
private:
	char m_letter;
	int m_offset_size;
	int m_size;
	int m_r;
	int m_g;
	int m_b;
	std::string m_font_name;
public:
	SpecialLetter(char letter, int size = 30, int r = 255, int g = 255, int b = 255, std::string font_name = "defaultfont.ttf");
	~SpecialLetter();
	void update();
	virtual int fake_w();
	virtual int fake_h();
protected:
//~ 	virtual void init(std::string text, int size = 30, int r = 255, int g = 255, int b = 255, std::string font_name = "defaultfont.ttf");


};
