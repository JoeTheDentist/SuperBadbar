
#ifndef _EDITOR_
#define _EDITOR_

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>

#include "collision_matrix.h"
#include "window.h"

class Editor{
private:
	bool m_leave;
	Window m_window;
	Collision_matrix m_collision_matrix;
	
	
public:
	Editor();
	Editor(std::string file_name);
	void edit();
	void right_clic();
	~Editor();
	
	
};



#endif