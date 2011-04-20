#ifndef ANIMATED_SET_MANAGER_H_INCLUDED
#define ANIMATED_SET_MANAGER_H_INCLUDED

#include "animated_set.h"

class Animated_set;

/**
 *  @class Animated_set_manager
 *  @brief Classe gréant les animated_sets
 */
class Animated_set_manager {
    private:
        std::list<Animated_set*> * m_sets;

        /**
         *  @brief Ajout d'un set
         */
        void add(Animated_set * set);
    public:
        /**
         *  @brief Constructeur
         */
        Animated_set_manager();

        /**
         *  @brief Destructeur
         */
        ~Animated_set_manager();

        /**
         *  @brief Ajouter un nophysic_set
         */
        void add_set(std::string anim_name, int x, int y, bool rand_pic=false, bool ended=false);

        /**
         *  @brief Ajouter un physic_set
         */
        void add_set(std::string anim_name, Rect pos, Rect speed);

        /**
         *  @brief Mise à jour : update_pos, update_speed
         */
        void update();

        /**
         *  @brief Vide la liste sans la détruire
         */
        void clear();

        /**
         *  @brief Charge les sets du niveau
         *  @param Analyser ouvert sur le fichier .lvl
         */
        void load_sets(Analyser * a);
};

#endif // ANIMATED_SET_MANAGER_H_INCLUDED
