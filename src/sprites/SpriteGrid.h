#ifndef SPRITEGRID_H
#define SPRITEGRID_H

#include "Sprite.h"

class AnimGrid;

class SpriteGrid : public Sprite
{
private:
    AnimGrid * m_animg;

public:
    /**
     * Ctor
     */
    SpriteGrid (std::string anim_name);

    /**
     * Dtor
     */
    virtual ~SpriteGrid();

    /**
     * Image a afficher
     *  +maj de m_pos
     */
    Surface *curr_pic();

    /**
     * Passe a l'image suivante
     */
    void next_pic();

    /**
     *  @brief Hauteur
     *  @return Hauteur
     */
    int h();

    /**
     *  @brief Largeur
     *  @return Largeur
     */
    int w();

    /**
     *	Set to a random picture
     */
    void rand_pic();

    /**
     *	Set the indexes of the pictures to display (max = 6 images)
     */
    void setPictures (int a, int b = -1, int c = -1, int d = -1, int e = -1, int f = -1);
};

#endif // SPRITEGRID_H
