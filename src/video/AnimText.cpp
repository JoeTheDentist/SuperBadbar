
#include "AnimText.h"

#include <video/SurfaceText.h>

AnimText::AnimText(std::string text, int begin_size, int end_size, int nb_pic)
{
    m_text = text;
    m_begin_size = begin_size;
    m_end_size = end_size;
    m_curr_num = 0;
    m_nb_pic = nb_pic;
    m_last_surf = NULL;
}

AnimText::~AnimText()
{
    if ( m_last_surf != NULL ) {
        delete m_last_surf;
    }
}

Surface * AnimText::curr_pic()
{
    if ( m_last_surf != NULL ) {
        delete m_last_surf;
    }
    m_last_surf = new SurfaceText(m_text, ((m_end_size-m_begin_size)*m_curr_num)/m_nb_pic + m_begin_size );
    return m_last_surf;
}

void AnimText::next_pic()
{
    m_curr_num++;
}

bool AnimText::interruptable()
{
    return false;
}

bool AnimText::deletable()
{
    return ( m_curr_num == m_nb_pic );
}

void AnimText::set_rect(Rect &pos)
{
    pos.h = m_last_surf->h();
    pos.w = m_last_surf->w();
}

void AnimText::set_img(int p)
{
    m_curr_num = p;
}
