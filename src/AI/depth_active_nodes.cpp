
#include "depth_active_nodes.h"

Depth_active_nodes::Depth_active_nodes()
{
    m_ens_nodes = new std::list<Node*>();
}

Depth_active_nodes::~Depth_active_nodes()
{
    m_ens_nodes->clear();
    delete m_ens_nodes;
}

bool Depth_active_nodes::is_empty()
{
    return m_ens_nodes->empty();
}

void Depth_active_nodes::to_empty()
{
    m_ens_nodes->clear();
}

void Depth_active_nodes::add(Node * n)
{
    m_ens_nodes->push_front(n);
}

void Depth_active_nodes::add(std::list<Node*> * nodes)
{
    for (std::list<Node *>::iterator it = nodes->begin();
				it != nodes->end(); it++) {
        add(*it);
    }
}

void Depth_active_nodes::add(std::list<Node*> * nodes, Node * node_ref)
{
    for (std::list<Node *>::iterator it = nodes->begin();
				it != nodes->end(); it++) {
        if ( (*it)->maybe_best(node_ref) ) {
            add(*it);
        }
    }
}

Node * Depth_active_nodes::remove()
{
    Node * n = m_ens_nodes->front();
    m_ens_nodes->pop_front();
    return n;
}

