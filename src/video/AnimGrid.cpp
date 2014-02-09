#include "AnimGrid.h"

#include "Grid.h"
#include "GridsContainer.h"

using namespace std;

AnimGrid::AnimGrid (string anim_name)
{
    m_grid = GridsContainer::GetInstance()->createGrid (anim_name);
    setPictures (0);
    m_curr = 0;
    m_phase = 0;
    //TODO (Guillaume) see if always cycle
    m_type = CYCLE;
}

AnimGrid::~AnimGrid()
{

}

Surface *AnimGrid::curr_pic()
{
    return m_grid->getImage (m_picToDisplay.at (m_curr % m_picToDisplay.size() ) );
}

void AnimGrid::next_pic()
{
    m_phase++;
    //TODO (Guillaume) not hardcoded
    m_phase %= 6;

    if ( m_phase == 0 )
    {
        if ( m_type != CYCLE && m_finished )    /* si on a fini sans etre en CYCLE, on garde la derniere image */
        {
            m_curr = m_picToDisplay.size() - 1;
        }
        else                            /* sinon on affiche les images cycliquement */
        {
            m_curr++;
            m_curr %= m_picToDisplay.size();
        }

        if ( m_type != CYCLE && ( m_curr == m_picToDisplay.size() - 1 ) ) /* une fois qu'on a fini une animation en force, on a fini */
        {
            m_finished = true;
        }
    }
}

void AnimGrid::set_rect (Rect &pos)
{
    pos.h = curr_pic()->h();
    pos.w = curr_pic()->w();
}

void AnimGrid::set_img (int i)
{
    m_curr = i % m_picToDisplay.size();
}

void AnimGrid::setPictures (int a, int b, int c, int d, int e, int f)
{
    m_picToDisplay.clear();
    m_picToDisplay.push_back (a);
    if (b != -1)
    {
        m_picToDisplay.push_back (b);
    }
    if (c != -1)
    {
        m_picToDisplay.push_back (c);
    }
    if (d != -1)
    {
        m_picToDisplay.push_back (d);
    }
    if (e != -1)
    {
        m_picToDisplay.push_back (e);
    }
    if (f != -1)
    {
        m_picToDisplay.push_back (f);
    }
}

bool AnimGrid::interruptable()
{
    return true;
}

bool AnimGrid::deletable()
{
    return false;
}
