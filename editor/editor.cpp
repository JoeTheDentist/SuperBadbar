

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

Editor::Editor(std::string file_name) :  m_leave(false), m_window(file_name), m_pic_list(file_name),/* m_collision_matrix(file_name),*/ m_file_name(file_name)
{

}


void Editor::save(std::string file_name)
{
	FILE* file = fopen(file_name.c_str(), "w+");
	std::cout << "Enregistrement du fichier " << file_name << std::endl;
	m_window.save(file);
	//~ m_collision_matrix.save(file);
	m_pic_list.save(file);
	fclose(file);
}



void Editor::edit()
{

	SDL_Event event;
	while (!m_leave){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				leave_editor();
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
					case SDLK_s:
						save(m_file_name);
						break;
					default:
						break;
				}
		}
		refresh();
	}
	
}

void Editor::refresh()
{
	m_window.update_background();
	m_pic_list.display_list(&m_window);
	m_window.refresh();
}


void Editor::right_clic(int x, int y)
{
	SDL_Event event;
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
	char choice = '0';
	std::string file_name;
	bool leave = false;
	std::cout << "Que voulez-vous faire?" << std::endl;
	std::cout << "1. Insérer une image" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
	while (!leave) {
		leave = true;
		std::cin >> choice;
		switch (choice) {
			case '1':
				std::cout << "Entrez le chemin de l'image à charger" << std::endl;
				std::cin >> file_name;
				insert_pic(file_name);
				break;
			
			
			default:
				leave = false;
				break;
		}
	}
	
}

void Editor::insert_pic(std::string file_name)
{
	SDL_Surface* pic = NULL;
	SDL_Event event;
	bool leave = false;
	pic = SDL_LoadBMP(file_name.c_str());
	SDL_Rect pos_pic;
	std::cout << "Insertion de l'image " << file_name << std::endl;
	while (!leave && !m_leave){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				leave_editor();
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					pos_pic = m_window.camera();
					pos_pic.x += event.button.x;
					pos_pic.y += event.button.y;
					m_pic_list.add(file_name, pos_pic);
					delete pic;
					leave = true;
				}
				else if (event.button.button == SDL_BUTTON_RIGHT) {
					right_clic(event.button.x, event.button.y);
				}
				break;

				
		}
		refresh();
	}
	
	
}

void Editor::leave_editor()
{
	m_leave = true;
}


Editor::~Editor()
{
	fprintf(stderr, "destruction de l'editor\n");
}