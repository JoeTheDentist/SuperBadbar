
#include "sprites_anim_table.h"

Sprite_anim_table::Sprite_anim_table(std::string anim_name, screen_level lvl)
{
    PRINT_CONSTR(3, "Construction de Sprite_anim_table")
    m_animt = new Anim_table(anim_name);
    m_lvl = lvl;
}

Sprite_anim_table::~Sprite_anim_table()
{
    PRINT_CONSTR(3, "destruction de Sprite_anim_table")
    delete m_animt;
}

Surface * Sprite_anim_table::curr_pic()
{
    Surface * s = m_animt->curr_pic();
    m_pos->h = s->h();
    m_pos->w = s->w();
    return s;
}

void Sprite_anim_table::next_pic()
{
    m_animt->next_pic();
}

void Sprite_anim_table::change_anim(state_player s, direction dir, bool fire ,bool phase_rand)
{
    m_animt->change_anim(s, dir, fire, phase_rand);
}

void Sprite_anim_table::change_anim(state_m s, direction dir, bool fire ,bool phase_rand)
{
    m_animt->change_anim(s, dir, fire, phase_rand);
}
