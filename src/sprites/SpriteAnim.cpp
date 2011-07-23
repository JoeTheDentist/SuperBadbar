

#include <stdlib.h>

#include "SpriteAnim.h"
#include "../video/AnimPic.h"
#include "../video/AnimText.h"

SpriteAnim::SpriteAnim(std::string anim_name, anim_type type, screen_level lvl, bool center)
{
    PRINT_CONSTR(1, "Construction de SpriteAnimTable")
    m_anim = new AnimPic(anim_name, type);
    m_lvl = lvl;
    m_no_pic = false;
    m_center = center;
}

SpriteAnim::SpriteAnim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl)
{
    PRINT_CONSTR(1, "Construction de SpriteAnimTable")
    m_anim = new AnimText(text,begin_size,end_size,nb_pic);
    m_lvl = lvl;
    m_no_pic = false;
    m_center = false;
}

SpriteAnim::~SpriteAnim()
{
    PRINT_CONSTR(3, "destruction de SpriteAnim")
    delete m_anim;
}

Surface * SpriteAnim::curr_pic()
{
    m_pos.h = m_anim->curr_pic()->h();
    m_pos.w = m_anim->curr_pic()->w();
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

int SpriteAnim::h()
{
    return m_anim->curr_pic()->h();
}

int SpriteAnim::w()
{
    return m_anim->curr_pic()->h();
}

void SpriteAnim::next_pic()
{
    /* p-e le mettre a un autre endroit */
    if ( m_anim->deletable() ) {
        m_to_delete = true;
    } else {
        m_anim->next_pic();
    }
}

void SpriteAnim::change_text_to(std::string text, int begin_size, int end_size, int nb_pic)
{
    delete m_anim;
    m_anim = new AnimText(text,begin_size,end_size,nb_pic);
}

void SpriteAnim::rand_pic()
{
    m_anim->set_img( rand() );
}
