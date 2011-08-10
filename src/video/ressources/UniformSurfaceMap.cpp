#include "UniformSurfaceMap.h"


UniformSurfaceMap::UniformSurfaceMap()
{
	
}

sf::Sprite* UniformSurfaceMap::getOrCreate(KeyMapSurfaceUnif key)
{
	return RessourcesMap<KeyMapSurfaceUnif, sf::Sprite>::getOrCreate(key);
}

sf::Sprite *UniformSurfaceMap::create(KeyMapSurfaceUnif key) 
{
	sf::Image *image = new sf::Image(key.m_width, key.m_height, sf::Color(key.m_r, key.m_g, key.m_b, key.m_alpha));
	sf::Sprite *sprite = new sf::Sprite();
	sprite->SetImage(*image);
	m_images.push_back(image);
	return sprite;
}
	
void UniformSurfaceMap::clear()
{
	RessourcesMap<KeyMapSurfaceUnif, sf::Sprite>::clear();
	for (std::list<sf::Image *>::iterator it = m_images.begin(); it != m_images.end(); ++it)
		delete (*it);
	m_images.clear();
}
