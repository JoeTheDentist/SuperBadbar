#ifndef _DASHBOARD_
#define _DASHBOARD_

#define POS_HEART_X 50
#define POS_HEART_Y 20
#define POS_WEAPON_X 50
#define POS_WEAPON_Y 60

#include <SDL/SDL_ttf.h>

#include "../items/weapons.h"

class Camera;
class Babar;
class Pictures_container;

class Dashboard {
private:
	TTF_Font *m_font;
	SDL_Color m_font_color;
	SDL_Surface *m_heart;
	SDL_Surface **m_weapons_pictures;
	Rect m_lifes_pos;
	Rect m_weapons_pos;
public:
	Dashboard(Pictures_container *pictures_container);
	~Dashboard();
	void draw_dashboard(int lifes, Camera *camera, Babar *babar);

};


#endif
