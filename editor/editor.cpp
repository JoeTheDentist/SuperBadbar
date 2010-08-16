

#include <iostream>
#include <stdint.h>
#include <string>


#include "editor.h"    
#include "collision_matrix.h"
#include "window.h"
#include "pic_list.h"

Editor::Editor()
{

}

Editor::Editor(std::string file_name) : m_leave(false), m_window(file_name)
{
	
}

void Editor::edit()
{

	SDL_Event event;
	while (!m_leave){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				m_leave = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_RIGHT) 
					right_clic(event.button.x, event.button.y);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_t:
						shell();
						break;
					default:
						break;
				}
		}
		m_window.update_background();
		m_window.refresh();
	}
	
}

void Editor::right_clic(int x, int y)
{
	SDL_Event event;
	std::cout << "yop" << std::endl;
	m_window.translate(x, y);
	int phase = 0;
	while (true){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				m_leave = true;
				break;
			case SDL_MOUSEBUTTONUP:    
				if (event.button.button == SDL_BUTTON_RIGHT){
					m_window.translate(-event.button.x, -event.button.y);
					return;
				}
				break;
			case SDL_MOUSEMOTION:
				if(phase == PIXELS_BEFORE_REFRESH){
					phase = 0;
					m_window.translate(-event.motion.x, -event.motion.y);
					m_window.update_background();
					m_window.refresh();
					m_window.translate(event.motion.x, event.motion.y);
				}
				else {
					phase++;
				}
				break;
		}

	}
	
}

void Editor::shell()
{
	
	std::cout << "Que voulez-vous faire?" << std::endl;
	
}


Editor::~Editor()
{
	fprintf(stderr, "destruction de l'editor\n");
}