
#include "sprites_manager.h"
#include "sprites_anim.h"
#include "sprites_anim_table.h"

Sprites_manager::Sprites_manager()
{
    m_to_sort = false;
    m_sprites = new std::list<Sprite*>();
}

Sprites_manager::~Sprites_manager()
{
    delete m_sprites;
}

void Sprites_manager::add(Sprite* s)
{
    m_sprites->push_front(s);
}

Sprite * Sprites_manager::add_anim(std::string anim_name, anim_type type, screen_level lvl)
{
    m_to_sort = true;
    Sprite * sprite = new Sprite_anim(anim_name, type, MIDDLEGROUND);
    add(sprite);
    return sprite;
}

Sprite * Sprites_manager::add_anim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl)
{
    m_to_sort = true;
    Sprite * sprite = new Sprite_anim(text, begin_size, end_size, nb_pic, MIDDLEGROUND);
    add(sprite);
    return sprite;
}

Sprite * Sprites_manager::add_table(std::string anim_name, screen_level lvl)
{
    m_to_sort = true;
    Sprite * sprite = new Sprite_anim_table(anim_name, MIDDLEGROUND);
    add(sprite);
    return sprite;
}

void Sprites_manager::update()
{
    if ( m_to_sort ) {
        m_to_sort = false;
        /* il parait que le tri est stable (très très important) mais c'est pas écrit directement sur la stl */
        /* la relation d'ordre est donnée par Sprite::operator<, pour la stabilité il faut du = aussi je pense... A voir */
        m_sprites->sort();
    }

    /* on passe aux images suivantes */
    /* au passage on regarde le images à supprimer */
    for (std::list<Sprite*>::iterator it=m_sprites->begin(); it!=m_sprites->end(); ) {
        (*it)->next_pic();
        if ( (*it)->to_delete() ) {
            /* suppression du sprite */
            delete (*it);
            (*it) = NULL;
			it = m_sprites->erase(it);
        } else {
            ++it;
        }
    }
}

void Sprites_manager::clear()
{
    m_sprites->clear();
}

void Sprites_manager::display_sprites(Camera * cam)
{
    for (std::list<Sprite*>::iterator it=m_sprites->begin(); it!=m_sprites->end(); ++it) {
        /* TODO faire éventuellement des positions fixe dans la structure de donnée de Sprite */
        cam->display_picture( (*it)->curr_pic(), (*it)->pos() );
    }
}
