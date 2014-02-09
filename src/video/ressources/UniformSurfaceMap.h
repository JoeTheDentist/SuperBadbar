#ifndef _UNIFORM_SURFACE_MAP_
#define _UNIFORM_SURFACE_MAP_

#include <util/RessourcesMap.h>
#include <SFML/Graphics.hpp>
#include <video/KeyMapSurfaceUnif.h>

#include <list>

class UniformSurfaceMap: public RessourcesMap<KeyMapSurfaceUnif, sf::Sprite>
{
protected:
    std::list<sf::Image *> m_images;
public:
    UniformSurfaceMap();

    virtual sf::Sprite *create (KeyMapSurfaceUnif key);

    virtual sf::Sprite* getOrCreate (KeyMapSurfaceUnif key);

    virtual void clear();

    sf::Sprite *getOrCreate (int width, int height, int r = 255, int g = 255, int b = 255, int alpha = 255)
    {
        return getOrCreate (KeyMapSurfaceUnif (width, height, r, g, b, alpha) );
    }


};


#endif
