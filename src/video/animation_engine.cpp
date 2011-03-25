
#include <string.h>

#include "animation_engine.h"
#include "../video/anim_table.h"
#include "../util/analyser.h"


Animation_engine::Animation_engine()
{
    m_phase = 0;
}

Animation_engine::~Animation_engine()
{
    std::list<anim_pos>::iterator it;
	for (it = m_anims.begin(); it != m_anims.end(); it++) {
        delete (*it).anim;
	}
}

void Animation_engine::init(std::string lvl_name)
{
    Analyser a;
    a.open(lvl_name);

    a.find_string("#Anims#");
    a.read_int();
	std::string anim_name = a.read_string();
	Rect pos;
	while(anim_name[0]!='!') {
		pos.x = a.read_int();
		pos.y = a.read_int();
        this->add(RACINE_R+anim_name, pos, CYCLE, false);
		anim_name = a.read_string();
    }

    a.close();
}

void Animation_engine::add(std::string pic, Rect pos, anim_type type, bool falling)
{
    Rect speed = {0,0,0,0};
    add(pic, pos, type, speed, falling);
}

void Animation_engine::add(std::string pic, Rect pos, anim_type type, Rect speed, bool falling)
{
    std::string test = pic;
    anim_pos a;
    a.pos = pos;
    a.speed = speed;
    a.falling = falling;

    /* création de l'animation */
    char k;
    for (k='0'; FileExists(pic+k+PICS_EXT); k++) {}
    std::string * link;
    link = new std::string[k-'0'];

    for (k='0'; FileExists(pic+k+PICS_EXT); k++) {
        link[k-'0'] = pic+k+PICS_EXT;
    }

    /* creation de l'animation */
    a.anim = new Animation(link,k-'0',type);
    a.anim->set_rect(a.pos);
    delete[] link;

    m_anims.push_front(a);
}

void Animation_engine::add(std::string pic, int x, int y)
{
    Rect pos;
    pos.x = x;
    pos.y = y;
    add(pic, pos, CYCLE, false);
}

void Animation_engine::add(std::string pic, int x, int y, anim_type type, int sx, int sy, bool falling)
{
    Rect pos;
    pos.x = x;
    pos.y = y;
    Rect speed;
    speed.x = sx;
    speed.y = sy;
    add(pic, pos, type, speed, falling);
}

void Animation_engine::display_anims(Camera * camera)
{
    std::list<anim_pos>::iterator it;
	for (it = m_anims.begin(); it != m_anims.end(); it++) {
	    camera->display_picture( (*it).anim->curr_pic(), &(*it).pos);
	}
}

void Animation_engine::update()
{
    std::list<anim_pos>::iterator it;
	for (it = m_anims.begin(); it != m_anims.end(); ) {
        if ( it->falling ) {
            gCollision->update_pos(it->pos, it->speed);
            it->speed.y += GRAVITE;

            /* continuité en x */
            it->speed.x = (9*it->speed.x)/10;
            it->pos.x += it->speed.x;
        }

	    if ( it->anim->deletable() ) {
	        delete it->anim;
			it = m_anims.erase(it);
		} else {
			++it;
		}
	}
}
