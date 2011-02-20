/**
 * 	@file node.h
 * 	@brief spécification de la classe Node
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date férvier 2010
 *
 */

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <list>


/**
 * 	@class Node
 * 	@brief Interface représentant un noeud pour b&b
 */
class Node {
    public:
        virtual bool is_solution()=0;
        virtual int depth()=0;
        virtual bool maybe_best(Node * n)=0;
        virtual std::list<Node*> * divide()=0;
        virtual double evaluation()=0;
};

#endif // NODE_H_INCLUDED
