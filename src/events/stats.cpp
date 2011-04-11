
#include "stats.h"
#include "../util/globals.h"
#include "../video/animation_engine.h"

class Animation_engine;

Stats::Stats()
{
    m_date=0;
    m_date_last_kill=0;
    m_kills=0;
    m_frenzy=0;
    m_msg_sent=false;
}

Stats::~Stats()
{

}

void Stats::update()
{
    m_date++;

    if ( m_date-m_date_last_kill >= INT_KILL ) {
        m_kills = 0;
        m_date_last_kill = 0;
    }

    alert();
}

void Stats::alert()
{
    /* Si aucun message n'a été émis */
    if ( !m_msg_sent ) {
        switch (m_kills) {
            case 2:
                m_msg_sent=true;
                gAnims->alert("DOUBLE KILL !");
                break;
            case 3:
                m_msg_sent=true;
                gAnims->alert("MULTI KILL !");
                break;
            case 5:
                m_msg_sent=true;
                gAnims->alert("MEGA KILL !");
                break;
            default:
                break;
        }
    }
}

void Stats::hit()
{
    /* Si on est touché, on remet tout à zéro */
    m_date_last_kill=0;
    m_kills=0;
    m_frenzy=0;
    m_msg_sent=false;
}

void Stats::kill()
{
    /* Si on a fait un kill il y a peu ou si c'est le premier de la série, on l'ajoute */
    if ( m_date-m_date_last_kill < INT_KILL || (m_date_last_kill==0 && m_kills==0) ) {
        m_kills++;
    }
    m_frenzy++;
    m_msg_sent=false;
    m_date_last_kill=m_date;
}
