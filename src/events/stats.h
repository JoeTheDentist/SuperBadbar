#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

#define INT_KILL 20 /* nombre de cycle maximal pour compter deux kills */

/**
 * Classe associée à un Babar, s'occupe de ses statistiques.
 */

class Stats {
    private:
        int m_date;             /* temps depuis execution, en nombre de cycles */
        int m_date_last_kill;   /* date de dernier kill */
        int m_kills;            /* kills successifs, limite temps */
        int m_frenzy;           /* kills successifs, sans se faire toucher */
        bool m_msg_sent;        /* si un message vient d'être émi */

        /**
         * Fonction d'affichage des messages
         */
        void alert();
    public:
        Stats();
        ~Stats();

        /**
         * Mise à jour : compte un cycle
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
