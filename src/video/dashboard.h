#ifndef _DASHBOARD_
#define _DASHBOARD_

#define POS_HEART_X 50
#define POS_HEART_Y 20

class Camera;

class Dashboard {
private:
	SDL_Surface *m_heart;
	SDL_Rect m_lifes_pos;
public:
	Dashboard();
	~Dashboard();
	void draw_dashboard(int lifes, Camera *camera);
	
};


#endif
