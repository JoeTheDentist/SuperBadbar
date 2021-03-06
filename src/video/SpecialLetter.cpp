/**
 * 	@file SpecialLetter.cpp
 * 	@brief Implementation de la classe SpecialLetter
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "SpecialLetter.h"


#include "util/debug.h"


SpecialLetter::SpecialLetter (char c, int size, int r, int g, int b, std::string font_name) :
    m_letter (c),
    m_offset_size (14),
    m_size (size),
    m_r (r),
    m_g (g),
    m_b (b),
    m_font_name (font_name)
{
    std::string str;
    str += m_letter;
    init (str, m_size + m_offset_size, m_r, m_g, m_b, m_font_name);
}

SpecialLetter::~SpecialLetter()
{
}

void SpecialLetter::update()
{
    if (m_offset_size == 0 )
        return;
    if (m_offset_size > 3)
    {
        m_offset_size -= 4;
    }
    else
    {
        m_offset_size = 0;
    }
    std::string str;
    str += m_letter;
    init (str, m_size + m_offset_size, m_r, m_g, m_b, m_font_name);
}

int SpecialLetter::fake_w()
{
    return (double (m_size) / double (m_size + m_offset_size) ) * double (SurfaceText::w() );
}

int SpecialLetter::fake_h()
{
    return (double (m_size) / double (m_size + m_offset_size) ) * double (SurfaceText::h() );
}


