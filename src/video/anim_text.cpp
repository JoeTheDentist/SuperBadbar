
#include "anim_text.h"

Anim_text::Anim_text(std::string text, int begin_size, int end_size, int nb_pic)
{
    m_text = text;
    m_begin_size = begin_size;
    m_end_size = end_size;
    m_curr_num = 0;
    m_nb_pic = nb_pic;
    m_last_surf = NULL;
}

Anim_text::~Anim_text()
{
    if ( m_last_surf != NULL ) {
        delete m_last_surf;
    }
}

Surface * Anim_text::curr_pic()
{
    if ( m_last_surf != NULL ) {
        delete m_last_surf;
    }
    m_last_surf = new Surface_text(m_text, ((m_end_size-m_begin_size)*m_curr_num)/m_nb_pic + m_begin_size );
    m_curr_num++;
    return m_last_surf;
}

bool Anim_text::interruptable()
{
    return false;
}

bool Anim_text::deletable()
{
    return ( m_curr_num == m_nb_pic );
}

void Anim_text::set_rect(Rect &pos)
{
    pos.h = m_last_surf->h();
    pos.w = m_last_surf->w();
}

void Anim_text::set_img(int p)
{
    m_curr_num = p;
}
