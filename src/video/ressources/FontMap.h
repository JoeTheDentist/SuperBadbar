#ifndef _FONT_MAP_
#define _FONT_MAP_

#include <util/RessourcesMap.h>

#include <SFML/Graphics.hpp>
#include <string>

class FontMap: public RessourcesMap<std::string, sf::Font>
{
public:
	virtual sf::Font *create(std::string key) 
	{
		sf::Font *font = new sf::Font();
		font->LoadFromFile(key);
		return font;
	}
	
	
};



#endif
