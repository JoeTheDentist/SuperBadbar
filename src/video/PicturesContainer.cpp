/**
 * 	@file PicturesContainer.h
 * 	@brief Implémentation de la classe PicturesContainer
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include "util/utils.h"
#include "../lib/SDL/include/SDL/SDL.h"
#include "../lib/SDL/include/SDL/SDL_image.h"
#include "../lib/SDL/include/SDL/SDL_ttf.h"
#ifndef DESACTIVATE_GFX
	#include "../lib/SDL/include/SDL/SDL_rotozoom.h"
#endif

#include "PicturesContainer.h"
#include "util/utils.h"
#include "util/globals.h"
#include "video/Camera.h"

PicturesContainer::PicturesContainer()
{
	PRINT_CONSTR(1, "Construction d'un PicturesContainer");
}

PicturesContainer::~PicturesContainer()
{
	resetMemory();
	PRINT_CONSTR(1, "Destruction d'un PicturesContainer");
}

sf::Sprite *PicturesContainer::load_picture(std::string key)
{
	std::map<std::string, sf::Sprite*>::iterator it = m_container.find(key);
	sf::Sprite *surf = NULL;
	if (it == m_container.end()) {
		sf::Image *image = new sf::Image;
		if (!image->LoadFromFile(key.c_str())) {
			PRINT_DEBUG(1, "impossible de charger l'image %s", key.c_str());
			delete image;
			return NULL;
		}
		surf = new sf::Sprite;
		surf->SetImage(*image);
		m_images.push_back(image);
		m_container.insert(std::pair<std::string, sf::Sprite*>(key, surf));
	} else {
		surf = (*it).second;
	}
	return surf;	
}

sf::String *PicturesContainer::loadSurfaceText(std::string text, int size, int r, int g, int b, std::string fontName)
{
	if (text == "")
		return NULL;
	KeyMapSurfaceText key(text, size, r, g, b, fontName);
	std::map<KeyMapSurfaceText, sf::String*>::iterator it = m_textContainer.find(key);
	sf::String *surf = NULL;
	if (it == m_textContainer.end()) {
		sf::Font *MyFont = m_fontsContainer.getOrCreate(FONTS_R + fontName);
		surf = new sf::String;
		surf->SetText(text.c_str());
		surf->SetFont(*MyFont);
		surf->SetSize(size);
		surf->SetColor(sf::Color(r, g, b));
		if (surf == NULL) {
			PRINT_DEBUG(1, "impossible de charger la surface ttf correspondant a  %s", text.c_str());
			return NULL;
		}
		m_textContainer.insert(std::pair<KeyMapSurfaceText, sf::String*>(key, surf));
	} else {
		surf = (*it).second;
	}
	return surf;
}

sf::Sprite *PicturesContainer::loadSurfaceUniform(int width, int height, int r, int g, int b, int alpha)
{
	return m_unifContainer.getOrCreate(width, height, r, g, b, alpha);
}

void PicturesContainer::resetMemory()
{
	std::map<std::string, sf::Sprite*>::iterator it;
	for (it = m_container.begin(); it != m_container.end(); it++) {
		delete it->second;
	}
	m_container.clear();
	std::map<KeyMapSurfaceText, sf::String*>::iterator ittext;
	for (ittext = m_textContainer.begin(); ittext != m_textContainer.end(); ittext++) {
		delete ittext->second;
	}
	m_textContainer.clear();
	std::list<sf::Image *>::iterator itimages;
	for (itimages = m_images.begin(); itimages != m_images.end(); itimages++) {
		delete *itimages;
	}
	m_images.clear();
	m_unifContainer.clear();
	m_fontsContainer.clear();
}
