
#include <cmath>
#include "AI_node.h"

AI_node::AI_node(Sprite * target, Collisions_manager * context,
            std::list<Rect*> * proj, int depth, int precision, Rect * dim, AI_node * daddy)
{
    m_target = target;
    m_context = context;
    m_proj = proj;
    m_precision = precision;
    m_depth = depth;
    m_dim = dim;

    m_daddy = daddy;
}

bool AI_node::is_solution()
{
    return m_depth==m_precision;
}

int AI_node::depth()
{
    return m_depth;
}

Rect AI_node::dim()
{
    return *m_dim;
}

AI_node * AI_node::daddy()
{
    return m_daddy;
}

bool AI_node::maybe_best(Node * n)
{
    /* attention, ne gère pas si ce n'est pas downcastable */
    //AI_node * na = (AI_node*)n;

    if ( n == NULL ) {
        return true;
    }

    return evaluation()>n->evaluation();
}

std::list<Node*> * AI_node::divide()
{
    /* Attention, ici c'est juste pour les monstres qui marchent, marche pas pour volants, faire avec polymph */
    /* On suppose qu'on a toujours les 4 possibilités */

    std::list<Node*> * l = new std::list<Node*>;

    Rect * lz = new Rect;
    Rect * rz = new Rect;
    Rect * uz = new Rect;
    Rect * dz = new Rect;
    *lz = *rz = *uz = *dz = *m_dim;
    lz->x -= m_dim->w;
    rz->x += m_dim->w;
    uz->y -= m_dim->h;
    dz->y += m_dim->h;

    /* calcul des nouveaux blocs */

    if ( is_solution() ) {
        return NULL;
    }

    if ( m_dim->x > m_target->position().x ) {
        /* si on est à droite de la cible */
        /* d'abord à gauche */
        /* ici on ne teste pas collision gauche : TODO */
        add_node(l,lz);
        /* saut et descente */
        if ( Collisions_manager::is_down_coll(m_context->down_collision_type(*m_dim)) ) {
            /* si on a une collision en dessous, on peut sauter */
            add_node(l,uz);
        }
        if ( !m_context->double_collision(*m_dim) ) {
            /* si on peut passer par en desssous */
            add_node(l,dz);
        }
        /* enfin à droite */
        /* idem gauche, TODO */
        add_node(l,rz);
    } else {
        /* si on est à gauche de la cible */
        /* d'abord à droite */
        /* ici on ne teste pas collision droite : TODO */
        add_node(l,rz);
        /* saut et descente */
        if (Collisions_manager::is_down_coll(m_context->down_collision_type(*m_dim)) ) {
            /* si on a une collision en dessous, on peut sauter */
            add_node(l,uz);
        }
        if ( !m_context->double_collision(*m_dim) ) {
            /* si on peut passer par en desssous */
            add_node(l,dz);
        }
        /* enfin à gauche*/
        /* idem droite, TODO */
        add_node(l,lz);
    }

    return l;
}

void AI_node::add_node(std::list<Node*> * l, Rect * z) {
    /* TODO : avoir les vraies dimensions du niveau
    passer par le collision_manager => collision_matrix... */
    if ( z->x > 0 && z->y-z->h > 0 ) {
        /* si la zone n'est pas en dehors de la carte */
        AI_node * n = new AI_node(m_target,m_context,m_proj,m_depth+1,m_precision,z,this);
        l->push_front(n);
    }
}

double AI_node::evaluation()
{
    /* pondération /r à la profondeur */
    double disp_weight = dist(*m_dim,m_target->position())/m_depth;

    double proj_weight = 0;

    /* si on a des projectiles dans la case... */
    for (std::list<Rect *>::iterator it = m_proj->begin();
				it != m_proj->end(); it++) {
        proj_weight -= 100/dist(*m_dim,**it); /* coef à changer'TODO, il faut qu'il compense dist*/
    }

    return disp_weight-proj_weight;
}

double AI_node::dist(Rect A, Rect B)
{
    return sqrt( (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y) );
}

