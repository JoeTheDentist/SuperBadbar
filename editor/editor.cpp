

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
					right_clic();
				break;
				
				

		}
	}
	
}

void Editor::right_clic()
{
	std::cout << "yop" << std::endl;
}

Editor::~Editor()
{
	fprintf(stderr, "destruction de l'editor\n");
}