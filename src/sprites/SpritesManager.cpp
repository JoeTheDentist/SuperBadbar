
#include "SpritesManager.h"
#include "SpriteAnim.h"
#include "SpriteAnimTable.h"
#include "util/debug.h"

SpritesManager::SpritesManager()
{
    m_sprites = new std::list<Sprite*>;
}

SpritesManager::~SpritesManager()
{
	PRINT_CONSTR(1, "Suppression du sprite manager");
    clear();
    delete m_sprites;
}

void SpritesManager::add(Sprite * s, bool back)
{
    if ( back ) {
        m_sprites->push_back(s);
    } else {
        m_sprites->push_front(s);
    }
}

Sprite * SpritesManager::add_anim(std::string anim_name, anim_type type, screen_level lvl, bool center)
{
    Sprite * sprite = new SpriteAnim(anim_name, type, MIDDLEGROUND, center);
    add(sprite);
    return sprite;
}

Sprite * SpritesManager::add_anim(std::string text, int begin_size, int end_size, int nb_pic, screen_level lvl)
{
    Sprite * sprite = new SpriteAnim(text, begin_size, end_size, nb_pic, MIDDLEGROUND);
    add(sprite);
    return sprite;
}

Sprite * SpritesManager::add_table(std::string anim_name, screen_level lvl)
{
    Sprite * sprite = new SpriteAnimTable(anim_name, MIDDLEGROUND);
    add(sprite, true);
    return sprite;
}

void SpritesManager::delete_dead_sprites()
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


void SpritesManager::update()
{
    /* on passe aux images suivantes */
    for (std::list<Sprite*>::iterator it=m_sprites->begin(); it!=m_sprites->end(); ++it) {
        (*it)->next_pic();
    }
}

void SpritesManager::clear()
{
    for (std::list<Sprite*>::iterator it=m_sprites->begin(); it!=m_sprites->end(); ) {
        delete (*it);
        (*it) = NULL;
        it = m_sprites->erase(it);
    }
}

void SpritesManager::display_sprites(Camera * cam)
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
