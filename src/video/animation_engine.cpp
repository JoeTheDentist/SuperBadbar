
#include <string.h>

#include "animation_engine.h"
#include "../video/anim_table.h"

Animation_engine::Animation_engine()
{
    m_phase = 0;
}

Animation_engine::~Animation_engine()
{
    /* essayer en appelant que le destructeur ? */
    std::list<anim_pos>::iterator it;
	for (it = m_anims.begin(); it != m_anims.end(); it++) {
        delete (*it).anim;
	}
}

void Animation_engine::add(std::string pic, Rect pos, anim_type type, bool falling)
{
    Rect speed = {0,0,0,0};
    add(pic, pos, type, speed, falling);
}

void Animation_engine::add(std::string pic, Rect pos, anim_type type, Rect speed, bool falling)
{
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
            /* continuité en y */
            /*if ( !Collisions_manager::is_down_coll(gCollision->down_collision_type(it->pos)) ) {
                it->pos.y += it->speed.y;
                it->speed.y += GRAVITE;
            }*/

            for (int speed_y = it->speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
                int coll = gCollision->down_collision_type(it->pos);
                if (Collisions_manager::is_down_coll(coll)){
                    speed_y = 0;
                    it->speed.y = 0;
                }
                else {
                    it->pos.y += BOX_SIZE;
                    if (it->pos.y + it->pos.h > gStatic->static_data_height())
                        it->pos.y = gStatic->static_data_height() - it->pos.h;
                }
            }
            /*it->pos.y += it->speed.y;*/
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
