#ifndef AI_NODE_H_INCLUDED
#define AI_NODE_H_INCLUDED

#include <list>

#include "node.h"
#include "../sprites/sprites.h"
#include "../util/globals.h"
#include "../game/collisions_manager.h"

class AI_node: public Node {
    private:
        Rect * m_dim;
        Sprite * m_target;
        Collisions_manager * m_context;
        std::list<Rect*> * m_proj;
        int m_precision;
        int m_depth;

        /**
         * @brief Distance grossi�re
         */
        double dist(Rect A, Rect B);

    public:
        AI_node * m_daddy;


        AI_node(Sprite * target, Collisions_manager * context,
            std::list<Rect*> * proj, int depth, int precision, Rect * dim, AI_node * daddy); /* ajouter des actions */
        bool is_solution();
        int depth();
        Rect dim();
        AI_node * daddy();

        /**
         * @brief Comparaison entre deux noeuds
         * @param n : Noeud avec qui on compare
         */
        bool maybe_best(Node * n);
        std::list<Node*> * divide();

        void add_node(std::list<Node*> * l, Rect * z);

        double evaluation();

};

#endif // AI_NODE_H_INCLUDED
