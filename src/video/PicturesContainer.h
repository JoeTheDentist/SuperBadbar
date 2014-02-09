/**
 * 	@file PicturesContainer.h
 * 	@brief Header de la classe PicturesContainer
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _PICTURES_CONTAINER_
#define _PICTURES_CONTAINER_

#include <map>
#include <list>
#include <string>

#include <video/KeyMapSurfaceText.h>
#include <video/KeyMapSurfaceUnif.h>
#include <SFML/Graphics.hpp>
#include <video/ressources/FontMap.h>
#include <video/ressources/UniformSurfaceMap.h>
#include <video/BigImage.h>

/**
 * 	@class PicturesContainer
 * 	@brief Charge les images de faÃ§on a optimiser la mémoire
 *
 *	Fournit une méthode load_IMG qui charge une image en fonction
 *	de son chemin, stocke cette image et en renvoie un pointeur.
 *	Si cette image a déjà été chargé une fois, la méthode renvoie
 *	un pointeur vers l'image déjà chargée.
 *
 *	PicturesContainer utilise un map pour stocker et retrouver
 *	les images en fonction de leur chemin.
 *
 *	Singleton.
 *
 *	@todo reorganiser la ou les localisations de PicturesContainer dans les autres classes
 *
 */
class PicturesContainer
{
private:
    FontMap m_fontsContainer;
    std::map<std::string, sf::Sprite*> m_container;
    std::map<KeyMapSurfaceText, sf::String*> m_textContainer;
    UniformSurfaceMap m_unifContainer;
    std::list<sf::Image *> m_images; // on garde les images ici pour pouvoir les deleter proprement
    std::list< std::pair< BigImage* , BigSprite* > > m_bigsContainer;

    static PicturesContainer *s_instance;

public:

    /**
     *	Getter of the instance
     */
    static PicturesContainer *GetInstance();

    /**
     *	Delete the instance
     */
    static void Destroy();

    /**
     * 	@brief Retourne un pointeur vers l'image demandée
     *	@param key Le chemin vers l'image
     *	@return Un pointeur vers l'image voulue
     */
    sf::Sprite *load_picture (std::string key);

    /*!
    *	@brief Retourne un pointeur vers l'image demandee
     *	@param key Le chemin vers l'image
     *	@return Un pointeur vers l'image voulue
    */
    BigSprite *loadBigPicture (std::string);

    /**
    *	@brief Retourne un pointeur vers la surface de texte demandee
    *	@param text Le texte de la surface
    *	@param size La taille du texte de la surface
    *	@param r La composante rouge du texte
    *	@param g La composante verte du texte
    *	@param b La composante bleue du texte
    *	@param fontNameLe nom de la police (qui sera charge dans le repertoire des polices)
    */
    sf::String *loadSurfaceText (std::string text, int size = 30, int r = 255, int g = 255, int b = 255, std::string fontName = "defaultfont.ttf");

    /**
    *	@brief Retourne un pointeur vers la surface de texte demandee
    *	@param width La largeur de la surface
    *	@param height La hauteur de la surface
    *	@param r La composante rouge de la surface
    *	@param g La composante verte de la surface
    *	@param b La composante bleue de la surface
    *	@param alpha La composante alpha de la surface
    */
    sf::Sprite *loadSurfaceUniform (int width, int height, int r = 255, int g = 255, int b = 255, int alpha = 255);


    /**
     * 	@brief Vide la memoire du picture container
     */
    void resetMemory();

private:
    /**
     * 	@brief Constructeur
     */
    PicturesContainer();

    /**
     * 	@brief Destructeur
     */
    ~PicturesContainer();
};


#endif
