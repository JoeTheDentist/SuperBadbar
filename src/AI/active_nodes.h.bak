/**
 * 	@file active_nodes.h
 * 	@brief spécification de la classe Active_nodes
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date férvier 2010
 *
 */

#ifndef ACTIVENODES_H_INCLUDED
#define ACTIVENODES_H_INCLUDED

#include <list>

#include "node.h"

/**
 * 	@class Active_nodes
 * 	@brief Interface représentant une stratégie pour b&b
 */
class Active_nodes {
    public:
        /**
         * @brief Si l'ensemble est vide.
         * @return true si la liste est vide
         */
        virtual bool is_empty()=0;

        /**
         * @brief Vide l'ensemble
         */
        virtual void to_empty()=0;

        /**
         * @brief Ajoute un noeud à l'ensemble
         * @param n : Noeud à ajouter
         */
        virtual void add(Node* n)=0;

        /**
         * @brief Ajoute un ensemble de noeuds à l'ensemble
         * @param nodes : Noeuds à ajouter
         */
        virtual void add(std::list<Node*> * nodes)=0;

        /**
         * @brief Ajoute un ensemble de noeuds à l'ensemble si meilleur que noeud de référence.
         * @param nodes : Noeuds à ajouter
         * @param node_ref : noeud de référence
         */
        virtual void add(std::list<Node*> * nodes, Node* node_ref)=0;

        /**
         * @brief Enlève le premier élément de l'ensemble.
         * @return noeud enlevé.
         */
        virtual Node * remove()=0;
};

#endif // ACTIVENODES_H_INCLUDED
