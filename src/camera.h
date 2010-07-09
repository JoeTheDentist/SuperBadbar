/**
 * La classe Camera pointe sur un sprite
 * Elle le suit dans ses déplacements avec update_pos()
 * et permet d'afficher des sprites à la bonne position
 **/

#ifndef _CAMERA_
#define _CAMERA_

#include <SDL/SDL.h>
#include <stdint.h>

#include "sprites.h"

class Camera {
private:
	SDL_Rect m_frame;	/* cadre de la camera */
	Sprite *m_cible;	/* sprite sur lequel pointe la camera */
public:
	Camera();		/* constructeur */
	Camera(Sprite *cible);	/* constructeur */
	~Camera();		/* destructeur */
	void update_pos();	/* mise à jour de la camera */
	void display_sprite(Sprite *sprite);
	SDL_Rect frame();	/* accesseur (m_frame) */
};
	



#endif