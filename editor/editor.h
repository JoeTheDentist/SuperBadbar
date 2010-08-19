
#ifndef _EDITOR_
#define _EDITOR_

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>

#include "collision_matrix.h"
#include "pic_list.h"
#include "window.h"

#define PIXELS_BEFORE_REFRESH 3

class Editor{
private:
	bool m_leave;
	Window m_window;
	Pic_list m_pic_list;
	Collision_matrix m_collision_matrix;
	std::string m_file_name;
	
	
public:
	Editor();
	Editor(std::string file_name);
	void save(std::string file_name);
	void edit();
	void refresh();
	void right_clic(int x, int y);
	void shell();
	void insert_pic(std::string file_name);
	void insert_last_pic();
	void leave_editor();
	void delete_pic();
	
	~Editor();
	
	
};



#endif