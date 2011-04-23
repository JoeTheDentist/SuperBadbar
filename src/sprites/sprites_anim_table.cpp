
#include "sprites_anim_table.h"

Sprite_anim_table::Sprite_anim_table(std::string anim_name, screen_level lvl)
{
    PRINT_CONSTR(3, "Construction de Sprite_anim_table")
    m_animt = new Anim_table(anim_name);
    m_lvl = lvl;
    m_no_pic = false;
}

Sprite_anim_table::~Sprite_anim_table()
{
    PRINT_CONSTR(3, "destruction de Sprite_anim_table")
    delete m_animt;
}

Surface * Sprite_anim_table::curr_pic()
{
    if ( !m_no_pic ) {
        return m_animt->curr_pic();
    } else {
        return NULL;
    }
}

void Sprite_anim_table::next_pic()
{
    m_animt->next_pic();
}

void Sprite_anim_table::change_anim(int s, direction dir, bool fire ,bool phase_rand)
{
    m_animt->change_anim(s, dir, fire, phase_rand);
}

int Sprite_anim_table::h()
{
    return m_animt->curr_pic()->h();
}

int Sprite_anim_table::w()
{
    return m_animt->curr_pic()->h();
}
