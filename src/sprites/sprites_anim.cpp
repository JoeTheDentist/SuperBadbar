

#include <stdlib.h>

#include "sprites_anim.h"
#include "../video/anim_pic.h"
#include "../video/anim_text.h"

Sprite_anim::Sprite_anim(std::string anim_name, anim_type type, screen_level lvl)
{
    PRINT_CONSTR(1, "Construction de Sprite_anim_table")
    m_anim = new Anim_pic(anim_name, type);
    m_lvl = lvl;
    m_no_pic = false;
}

Sprite_anim::Sprite_anim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl)
{
    PRINT_CONSTR(1, "Construction de Sprite_anim_table")
    m_anim = new Anim_text(text,begin_size,end_size,nb_pic);
    m_lvl = lvl;
    m_no_pic = false;
}

Sprite_anim::~Sprite_anim()
{
    PRINT_CONSTR(1, "destruction de Sprite_anim_table")
    delete m_anim;
}

Surface * Sprite_anim::curr_pic()
{
    if ( !m_no_pic ) {
        if ( m_to_delete ) {
            return NULL;
        } else {
            return m_anim->curr_pic();
        }
    } else {
        return NULL;
    }
}

int Sprite_anim::h()
{
    return m_anim->curr_pic()->h();
}

int Sprite_anim::w()
{
    return m_anim->curr_pic()->h();
}

void Sprite_anim::next_pic()
{
    /* p-e le mettre à un autre endroit */
    if ( m_anim->deletable() ) {
        m_to_delete = true;
    } else {
        m_anim->next_pic();
    }
}

void Sprite_anim::change_text_to(std::string text, int begin_size, int end_size, int nb_pic)
{
    delete m_anim;
    m_anim = new Anim_text(text,begin_size,end_size,nb_pic);
}

void Sprite_anim::rand_pic()
{
    m_anim->set_img( rand() );
}
