
#include "sprites_manager.h"
#include "sprites_anim.h"
#include "sprites_anim_table.h"

Sprites_manager::Sprites_manager()
{
    m_sprites = new std::list<Sprite*>;
}

Sprites_manager::~Sprites_manager()
{
    clear();
    delete m_sprites;
}

void Sprites_manager::add(Sprite * s)
{
    m_sprites->push_front(s);
}

Sprite * Sprites_manager::add_anim(std::string anim_name, anim_type type, screen_level lvl, bool center)
{
    Sprite * sprite = new Sprite_anim(anim_name, type, MIDDLEGROUND, center);
    add(sprite);
    return sprite;
}

Sprite * Sprites_manager::add_anim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl)
{
    Sprite * sprite = new Sprite_anim(text, begin_size, end_size, nb_pic, MIDDLEGROUND);
    add(sprite);
    return sprite;
}

Sprite * Sprites_manager::add_table(std::string anim_name, screen_level lvl)
{
    Sprite * sprite = new Sprite_anim_table(anim_name, MIDDLEGROUND);
    add(sprite);
    return sprite;
}

void Sprites_manager::delete_dead_sprites()
{
    for (std::list<Sprite*>::iterator it=m_sprites->begin(); it!=m_sprites->end(); ) {
        if ( (*it)->to_delete() ) {
            /* suppression du sprite */
            delete (*it);
//~             (*it) = NULL;
			it = m_sprites->erase(it);
        } else {
            ++it;
        }
    }
}


void Sprites_manager::update()
{
    /* on passe aux images suivantes */
    for (std::list<Sprite*>::iterator it=m_sprites->begin(); it!=m_sprites->end(); ++it) {
        (*it)->next_pic();
    }
}

void Sprites_manager::clear()
{
    for (std::list<Sprite*>::iterator it=m_sprites->begin(); it!=m_sprites->end(); ) {
        delete (*it);
        (*it) = NULL;
        it = m_sprites->erase(it);
    }
}

void Sprites_manager::display_sprites(Camera * cam)
{
    for (std::list<Sprite*>::iterator it=m_sprites->begin(); it!=m_sprites->end(); ++it) {
        /* si on doit centrer l'image */
        if ( (*it)->center() ) {
            Rect pos = *(*it)->pos();
            pos.x -= pos.w/2;
            pos.y -= pos.h/2;
            cam->display_picture( (*it)->curr_pic(), &pos ) ;
        } else {
            cam->display_picture( (*it)->curr_pic(), (*it)->pos() );
        }
    }
}
