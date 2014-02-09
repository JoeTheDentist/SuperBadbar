#ifndef ANIMGRID_H
#define ANIMGRID_H

#include <vector>

#include "Anim.h"

class Grid;

class AnimGrid : public Anim
{
private:
    std::vector<int> m_picToDisplay;	//idexes if the images to display
    Grid *m_grid;	//all the images displayable by the animation

public:
    /**
     *	Ctor
     *  @param string donnant l'adresse du paquet d'image a charger
     */
    AnimGrid (std::string anim_name);

    /**
     *	Dtor
     */
    virtual ~AnimGrid();

    /**
     *	Getter
     */
    Surface * curr_pic();

    /**
     *	Switch to the next picture
     */
    void next_pic();

    /**
     *	Set hauteur et largeur en fonction de l'image courante
     *	@param Rect a modifier
     */
    void set_rect (Rect &pos);

    /**
     *	Sets the index of current image
     *	@param i: index
     */
    void set_img (int i);

    /**
     *	Set the indexes of the pictures to display
     */
    void setPictures (int a, int b = -1, int c = -1, int d = -1, int e = -1, int f = -1);

    /**
     * @brief si on peut interrompre l'animation.
     * @return booleen, true si on peut l'interrompre.
     */
    bool interruptable();

    /**
     * @brief si on peut supprimer l'animation.
     * @return booleen, true si on peut la suppr.
     */
    bool deletable();
};

#endif // ANIMGRID_H
