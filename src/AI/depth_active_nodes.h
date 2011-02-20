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
         * @brief Ajoute un noeud � l'ensemble
         * @param n : Noeud � ajouter
         */
        void add(Node* n);

        /**
         * @brief Ajoute un ensemble de noeuds � l'ensemble
         * @param nodes : Noeuds � ajouter
         */
        void add(std::list<Node*> * nodes);

        /**
         * @brief Ajoute un ensemble de noeuds � l'ensemble si meilleur que noeud de r�f�rence.
         * @param nodes : Noeuds � ajouter
         * @param node_ref : noeud de r�f�rence
         */
         void add(std::list<Node*> * nodes, Node* node_ref);

        /**
         * @brief Enl�ve le premier �l�ment de l'ensemble.
         * @return noeud enlev�.
         */
         Node * remove();
};

#endif // DEPTH_ACTIVE_NODES_H_INCLUDED
