
#include <string.h>

#include "animation_engine.h"
#include "../video/anim_table.h"
#include "../util/analyser.h"
#include "../video/anim_text.h"
/* Temp */
#include "../sprites/babar.h"


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
        this->add(PIC_R+"animations/"+anim_name, pos, CYCLE, false);
		anim_name = a.read_string();
    }

    a.close();



    /* Temp */
    Rect pos_temp = {400,300,0,0};
    add(new Anim_text("TEST !!!!!", 250, 100, 30), pos_temp, ENDED, false);

}

void Animation_engine::add(Animation * anim, Rect pos, anim_type type, bool falling)
{
    anim_pos a;
    a.pos = pos;
    Rect speed = {0};
    a.speed = speed;
    a.falling = falling;
    a.anim = anim;
    a.fixe = true;
    m_anims.push_front(a);
}

void Animation_engine::add(std::string pic, Rect pos, anim_type type, bool falling)
{
    Rect speed = {0};
    add(pic, pos, type, speed, falling);
}

void Animation_engine::add(std::string pic, Rect pos, anim_type type, Rect speed, bool falling)
{
    std::string test = pic;
    anim_pos a;
    a.pos = pos;
    a.speed = speed;
    a.falling = falling;
    a.fixe=false;

    /* création de l'animation */
    int k;
    k=0;
    char num[3];
    sprintf(num,"%d",k);
    while ( FileExists(pic+num+PICS_EXT) ) {
        k++;
        sprintf(num,"%d",k);
    }
    std::string * link;
    link = new std::string[k];

    k=0;
    sprintf(num,"%d",k);
    while ( FileExists(pic+num+PICS_EXT) ) {
        link[k] = pic+num+PICS_EXT;
        k++;
        sprintf(num,"%d",k);
    }

    /* creation de l'animation */
    a.anim = new Anim_pic(link,k,type);
    if ( type == CYCLE ) {
        a.anim->set_img(rand()%k);
    }
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
    Rect pos;
    Surface * surf;
	for (it = m_anims.begin(); it != m_anims.end(); it++) {
	    pos = (*it).pos;
	    surf = (*it).anim->curr_pic();
	    /* Si on est en animation fixe, la position est le centre de l'image */
	    if ( (*it).fixe ) {
            pos.x -= surf->w()/2;
            pos.y -= surf->h()/2;
	    }
	    camera->display_picture( surf, &pos, (*it).fixe);
	}
}

void Animation_engine::update()
{
    std::list<anim_pos>::iterator it;
	for (it = m_anims.begin(); it != m_anims.end(); ) {
        if ( it->falling ) {
            gCollision->get_matrix()->update_pos(it->pos, it->speed);
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
