/**
 * La classe Camera pointe sur un sprite
 * Elle le suit dans ses déplacements avec update_pos()
 * et permet d'afficher des sprites à la bonne position avec display_sprite
 * La camera suit le sprite pointé sauf lorsqu'il arrive aux limites du niveau
 **/

#ifndef _CAMERA_
#define _CAMERA_

#include <SDL/SDL.h>
#include <stdint.h>

#include "sprites.h"
#include "statics.h"

class Babar;
class Monster;
class Projectile;
class Sprite;
class Level;

class Camera {
private:
	SDL_Rect m_frame;	/* cadre de la camera */
	Sprite *m_target;	/* sprite sur lequel pointe la camera */
public:
	Camera();								/* constructeur */
	Camera(Sprite *target);					/* constructeur */
	~Camera();								/* destructeur */
	void update_pos(Level *level);						/* mise à jour de la camera */
	void display_background(SDL_Surface *background); /* affichage d'un fond d'écran */
	void display_sprite(Babar *babar);      /* affichage d'un Babar */
	void display_sprite(Monster *monster);  /* affichage d'un monstre */
	void display_sprite(Projectile * proj); /* affichage d'un projectile */
	void display_static(Static *sttc);
	SDL_Rect frame();	/* accesseur (m_frame) */
};



#endif
