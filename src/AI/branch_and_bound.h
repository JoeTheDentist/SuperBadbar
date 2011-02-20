/**
 * 	@file active_nodes.h
 * 	@brief sp�cification de la classe Active_nodes
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date f�rvier 2010
 *
 */

#ifndef BRANCH_AND_BOUND_H_INCLUDED
#define BRANCH_AND_BOUND_H_INCLUDED

#include "node.h"
#include "active_nodes.h"

class Branch_and_bound {
    private:
        Active_nodes * m_act_nodes;
        Node * m_root;
        Node * m_best_solution;

    public:
        /**
         * @brief Constructeur
         * @param root : racine
         * @param strat : strat�gie de parcours
         * /!\\ Attention, arg pass�s doit �tre allou�s et non utilis�s � l'ext�rieur
         */
        Branch_and_bound(Node * root, Active_nodes * strat);

        ~Branch_and_bound();

        /**
         * @brief R�solution du probl�me
         * @return solution du probl�me.
         */
        Node * solve();
};

#endif // BRANCH_AND_BOUND_H_INCLUDED
