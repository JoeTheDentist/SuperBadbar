
#include "sprites_anim.h"
#include "../video/anim_pic.h"
#include "../video/anim_text.h"

Sprite_anim::Sprite_anim(std::string anim_name, anim_type type, screen_level lvl)
{
    PRINT_CONSTR(1, "Construction de Sprite_anim_table")
    m_anim = new Anim_pic(anim_name, type);
    m_lvl = lvl;
}

Sprite_anim::Sprite_anim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl)
{
    PRINT_CONSTR(1, "Construction de Sprite_anim_table")
    m_anim = new Anim_text(text,begin_size,end_size,nb_pic);
    m_lvl = lvl;
}

Sprite_anim::~Sprite_anim()
{
    PRINT_CONSTR(1, "destruction de Sprite_anim_table")
    delete m_anim;
}

Surface * Sprite_anim::curr_pic()
{
    Surface * s = m_anim->curr_pic();
    m_pos->h = s->h();
    m_pos->w = s->w();
    return s;
}

void Sprite_anim::next_pic()
{
    /* p-e le mettre à un autre endroit */
    if ( m_anim->deletable() ) {
        m_to_delete = true;
    }
    m_anim->next_pic();
}

void Sprite_anim::change_text_to(std::string text, int begin_size, int end_size, int nb_pic)
{
    delete m_anim;
    m_anim = new Anim_text(text,begin_size,end_size,nb_pic);
}
