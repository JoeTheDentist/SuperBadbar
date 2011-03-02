/**
 * 	@file animation_engine.h
 * 	@brief Conteneur et joueur d'animation indépendantes
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _ANIMATION_ENGINE_
#define _ANIMATION_ENGINE_

#include <map>

#include "../video/surface.h"
#include "../video/animation.h"
#include "../video/camera.h"


struct anim_pos {
    Rect * pos;
    Animation * anim;
};

class Animation_engine {
	private:
        /* listes des noms des animations à jouer */
        std::list<anim_pos> m_anims;

	public:
        Animation_engine();
        ~Animation_engine();
        void add(std::string pic, Rect pos);
        void add(std::string pic, int x, int y);
        void display_anims(Camera * camera);

        /* TODO, virer les anim out of date
        TODO faire les animations qui sont finies à laisser et les autres */
        void update();
};

#endif
