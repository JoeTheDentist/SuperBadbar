#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class Surface;

/**
 *	Class aimed to cut one image into other small images.
 *	It cuts the image according to the pink color in the image.
 *	Then grid store the cut images into an array.
 */
class Grid
{
public:
	/**
	 *	Ctor
	 *	@param imgPath: path to the image to cut according to the pink lines
	 */
	Grid(std::string imgPath);

	/**
	 *	Dtor
	 */
	~Grid();

	/**
	 *	Getter
	 *	@param i: position of the wanted image
	 *	@return image at position i
	 */
	Surface *getImage(int i);

private:
	Surface *m_originalImage;
	std::vector<Surface*> m_images;
	std::vector<sf::Image*> m_saveImages;
	std::vector<sf::Sprite*> m_saveSprites;
};

#endif // GRID_H
