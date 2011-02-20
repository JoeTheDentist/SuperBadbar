#ifndef DEPTH_ACTIVE_NODES_H_INCLUDED
#define DEPTH_ACTIVE_NODES_H_INCLUDED

#include "node.h"
#include "active_nodes.h"

class Depth_active_nodes: public Active_nodes {
    private:
        std::list<Node*> * m_ens_nodes;

    public:
        Depth_active_nodes();
        ~Depth_active_nodes();
        /**
         * @brief Si l'ensemble est vide.
         * @return true si la liste est vide
         */
         bool is_empty();

        /**
         * @brief Vide l'ensemble
         */
         void to_empty();

        /**
         * @brief Ajoute un noeud à l'ensemble
         * @param n : Noeud à ajouter
         */
        void add(Node* n);

        /**
         * @brief Ajoute un ensemble de noeuds à l'ensemble
         * @param nodes : Noeuds à ajouter
         */
        void add(std::list<Node*> * nodes);

        /**
         * @brief Ajoute un ensemble de noeuds à l'ensemble si meilleur que noeud de référence.
         * @param nodes : Noeuds à ajouter
         * @param node_ref : noeud de référence
         */
         void add(std::list<Node*> * nodes, Node* node_ref);

        /**
         * @brief Enlève le premier élément de l'ensemble.
         * @return noeud enlevé.
         */
         Node * remove();
};

#endif // DEPTH_ACTIVE_NODES_H_INCLUDED
