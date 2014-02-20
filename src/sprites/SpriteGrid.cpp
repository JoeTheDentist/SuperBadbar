#include "SpriteGrid.h"

#include "video/AnimGrid.h"

SpriteGrid::SpriteGrid (std::string anim_name)
{
    PRINT_CONSTR (3, "Construction de SpriteGrid");
    m_animg = new AnimGrid (anim_name);
    m_no_pic = false;
    m_center = false;
    m_lvl = MIDDLEGROUND;
}

SpriteGrid::~SpriteGrid()
{
    PRINT_CONSTR (3, "destruction de SpriteGrid");
    delete m_animg;
}

Surface * SpriteGrid::curr_pic()
{
    if ( !m_no_pic )
    {
        return m_animg->curr_pic();
    }
    else
    {
        return NULL;
    }
}

void SpriteGrid::next_pic()
{
    m_animg->next_pic();
}

void SpriteGrid::setPictures (int a, int b, int c, int d, int e, int f)
{
    m_animg->setPictures (a, b, c, d, e, f);
}

int SpriteGrid::h()
{
    return m_animg->curr_pic()->h();
}

int SpriteGrid::w()
{
    return m_animg->curr_pic()->h();
}

void SpriteGrid::rand_pic()
{
    m_animg->set_img ( rand() );
}
