#ifndef _MAIN_TITLE_H_
#define _MAIN_TITLE_H_

#define MAIN_TITLE_R 255
#define MAIN_TITLE_G 100
#define MAIN_TITLE_B 0
#define MAIN_TITLE_SIZE 60
#define MAIN_TITLE_OFFSET 60
#define MAIN_TITLE_Y 200
#define MAIN_TITLE_BACKGROUND_OFFSET_W 30
#define MAIN_TITLE_BACKGROUND_OFFSET_H 10
#define MAIN_TITLE_BACK_R 50
#define MAIN_TITLE_BACK_G 50
#define MAIN_TITLE_BACK_B 50
#define MAINT_TITLE_BACKGROUND_ALPHA 175

#include <string>

#include <util/Rect.h>

class Camera;
class Surface;

class MainTitle {
protected:
	Surface *m_surface;
	Surface *m_surface_background;
	std::string m_title;
	int m_y;
	int m_size;
	int m_offset;
	Rect m_posbackground;
	Rect m_pos;

public:
	MainTitle(std::string title);
	~MainTitle();
	void update();
	void display(Camera *camera);
protected:
	void recompute_surface();
	void recompute_pos();


};


#endif

