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
    Rect pos;
    Animation * anim;
    Rect speed;
    bool falling;
};

class Animation_engine {
	private:
        /* listes des noms des animations à jouer */
        std::list<anim_pos> m_anims;
        int m_phase;

	public:
        Animation_engine();
        ~Animation_engine();
        void add(std::string pic, Rect pos, anim_type type, bool falling);
        void add(std::string pic, Rect pos, anim_type type, Rect speed, bool falling);
        void add(std::string pic, int x, int y);
        void add(std::string pic, int x, int y, anim_type type, int sx, int sy, bool falling);
        void display_anims(Camera * camera);

        void update();
};

#endif
