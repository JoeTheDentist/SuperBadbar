/**
 * 	@file active_nodes.cpp
 * 	@brief source de la classe Active_nodes
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date f�rvier 2010
 *
 */

#include "branch_and_bound.h"

Branch_and_bound::Branch_and_bound(Node * root, Active_nodes * strat) {
    m_root = root;
    m_act_nodes = strat;
}

Branch_and_bound::~Branch_and_bound()
{
    /* Attention cela impose que les param du construteur soit pass� en les allouant */
    delete m_root;
    delete m_act_nodes;
}

Node * Branch_and_bound::solve() {
    // initialisations
    m_best_solution = NULL;
    m_act_nodes->to_empty();
    m_act_nodes->add(m_root);

    while (!m_act_nodes->is_empty()) {
        // on recupere le prochain noeud a traiter
        Node * n = m_act_nodes->remove();

        // ce noeud peut-il amener une meilleure solution?
        if (n->maybe_best(m_best_solution)) {
            if (n->is_solution()) {
                // meilleure solution jusque la, on la garde et on elague
                m_best_solution = n;
            } else {
                // division du noeud et ajout de ses fils dans les
                // actifs. Seuls les noeuds de meilleure
                // evaluation que la solution courante seront
                // ajoutes (les autres seront donc elagues)
                m_act_nodes->add(n->divide(), m_best_solution);
            }
        }
        // Sinon on ne fait rien, le noeud est elague!
    }
    // on retourne la meilleure solution trouvee, eventuellement null
    return m_best_solution;
}
