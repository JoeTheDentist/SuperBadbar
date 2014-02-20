#include <stdlib.h>

#include "SpriteAnimTable.h"

SpriteAnimTable::SpriteAnimTable (std::string anim_name, screen_level lvl)
{
    PRINT_CONSTR (3, "Construction de SpriteAnimTable");
    m_animt = new AnimTable (anim_name);
    m_lvl = lvl;
    m_no_pic = false;
    m_center = false;
}

SpriteAnimTable::~SpriteAnimTable()
{
    PRINT_CONSTR (3, "destruction de SpriteAnimTable");
    delete m_animt;
}

Surface * SpriteAnimTable::curr_pic()
{
    if ( !m_no_pic )
    {
        return m_animt->curr_pic();
    }
    else
    {
        return NULL;
    }
}

void SpriteAnimTable::next_pic()
{
    m_animt->next_pic();
}

void SpriteAnimTable::change_anim (int s, Direction dir, bool fire , bool phase_rand)
{
    m_animt->change_anim (s, dir, fire, phase_rand);
}

int SpriteAnimTable::h()
{
    return m_animt->curr_pic()->h();
}

int SpriteAnimTable::w()
{
    return m_animt->curr_pic()->h();
}

void SpriteAnimTable::rand_pic()
{
    m_animt->set_img ( rand() );
}
