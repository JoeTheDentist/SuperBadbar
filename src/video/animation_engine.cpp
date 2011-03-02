
#include <string.h>

#include "animation_engine.h"
#include "../video/anim_table.h"

Animation_engine::Animation_engine()
{

}

Animation_engine::~Animation_engine()
{
    /* essayer en appelant que le destructeur ? */
    std::list<anim_pos>::iterator it;
	for (it = m_anims.begin(); it != m_anims.end(); it++) {
        delete (*it).anim;
        delete (*it).pos;
	}
}

void Animation_engine::add(std::string pic, Rect pos)
{
    anim_pos a;
    a.pos = new Rect;
    a.pos->x = pos.x;
    a.pos->y = pos.y;

    /* création de l'animation */
    char k;
    for (k='0'; FileExists(pic+k+PICS_EXT); k++) {}
    std::string * link;
    link = new std::string[k-'0'];

    for (k='0'; FileExists(pic+k+PICS_EXT); k++) {
        link[k-'0'] = pic+k+PICS_EXT;
    }

    /* creation de l'animation */
    a.anim = new Animation(link,k-'0',false);
    a.anim->set_rect(*a.pos);
    delete[] link;

    m_anims.push_front(a);
}

void Animation_engine::add(std::string pic, int x, int y)
{
    Rect pos;
    pos.x = x;
    pos.y = y;
    add(pic, pos);
}

void Animation_engine::display_anims(Camera * camera)
{
    std::list<anim_pos>::iterator it;
	for (it = m_anims.begin(); it != m_anims.end(); it++) {
	    Static * s = new Static((*it).anim->curr_pic(),*(*it).pos);
	    /* serait mieux... mais marche pas */
	    /*camera->display_picture( (*it).anim->curr_pic(), (*it).pos);*/
	    camera->display(s);
	    delete s;
	}
}

void update()
{

}
