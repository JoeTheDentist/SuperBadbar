#include "Grid.h"

#include "Surface.h"
#include "PicturesContainer.h"

//TEMP
#include <iostream>

using namespace std;

Grid::Grid (string imgPath)
{
    sf::Sprite *sprite = PicturesContainer::GetInstance()->load_picture (imgPath);
    sf::Image *img = new sf::Image (*sprite->GetImage() );
    unsigned int caseHeight = 0;
    unsigned int caseWidth = 0;
    unsigned int height = 0;
    unsigned int width = 0;

    for (unsigned int i = 1; i < img->GetHeight(); ++i)
    {
        sf::Color currColor = img->GetPixel (1, i);
        if ( (int) currColor.r == 255 &&
                (int) currColor.g == 0 &&
                (int) currColor.b == 255)
        {
            caseHeight = i - 1;
            break;
        }
    }
    for (unsigned int j = 1; j < img->GetWidth(); ++j)
    {
        sf::Color currColor = img->GetPixel (j, 1);
        if ( (int) currColor.r == 255 &&
                (int) currColor.g == 0 &&
                (int) currColor.b == 255)
        {
            caseWidth = j - 1;
            break;
        }
    }

    height = img->GetHeight() / (caseHeight + 2);
    width = img->GetWidth() / (caseWidth + 2);

    for (unsigned int i = 0; i < height; ++i)
    {
        for (unsigned int j = 0; j < width; ++j)
        {
            sf::Image *currImg = new sf::Image (caseWidth, caseHeight);
            sf::IntRect pos (j * caseWidth + 1 + 2 * j,
                             i * caseHeight + 1 + 2 * i,
                             (j + 1) *caseWidth + 1 + 2 * j,
                             (i + 1) *caseHeight + 1 + 2 * i);
            currImg->Copy (*sprite->GetImage(),
                           0,
                           0,
                           pos);
            cout << currImg->GetHeight() << endl;
            sf::Sprite *currSprite = new sf::Sprite (*currImg);
            m_saveImages.push_back (currImg);
            m_saveSprites.push_back (currSprite);
            m_images.push_back (new Surface (currSprite) );
        }
    }

    delete img;
}

Grid::~Grid()
{
    for (vector<sf::Image*>::iterator it = m_saveImages.begin();
            it < m_saveImages.end();
            ++it)
    {
        delete (*it);
        (*it) = NULL;
    }

    for (vector<Surface*>::iterator it = m_images.begin();
            it < m_images.end();
            ++it)
    {
        delete (*it);
        (*it) = NULL;
    }

    for (vector<sf::Sprite*>::iterator it = m_saveSprites.begin();
            it < m_saveSprites.end();
            ++it)
    {
        delete (*it);
        (*it) = NULL;
    }
}

Surface *Grid::getImage (int i)
{
    return m_images[i % m_images.size()];
}
