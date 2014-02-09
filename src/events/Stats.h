#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

#define INT_KILL 50 /* nombre de cycle maximal pour compter deux kills */

#include "sprites/Sprite.h"

/**
 * TODO (re) / TOCOMMENT
 * Classe associee a un Babar, s'occupe de ses statistiques.
 */

class Stats
{
private:
    int m_date;             /* temps depuis execution, en nombre de cycles */
    int m_date_last_kill;   /* date de dernier kill */
    int m_kills;            /* kills successifs, limite temps */
    int m_frenzy;           /* kills successifs, sans se faire toucher */
    bool m_msg_sent;        /* si un message vient d'etre emi */
    Sprite * m_sprite;      /* pour affichage */

    /**
    	 * Fonction d'affichage des messages
    	 */
    void alert();
public:
    Stats();
    ~Stats();

    /**
    	 * Mise a jour : compte un cycle, raz si besoin
    	 */
    void update();

    /**
    	 * Si Babar se fait toucher
    	 */
    void hit();

    /**
    	 * Si Babar tue un monstre
    	 */
    void kill();
};

#endif // STATS_H_INCLUDED
