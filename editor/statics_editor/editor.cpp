#include <iostream>
#include <stdint.h>
#include <string>

#include "editor.h"
#include "SDL/SDL.h"

Editor::Editor(std::string static_name) : m_window(static_name), m_static(static_name), m_curr_coll(DOWN_COLL), m_leave(false)
{

}


Editor::~Editor()
{
	
}


void Editor::edit()
{
	SDL_Event event;
	refresh_screen();
	while (!m_leave){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				leave();
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
					case SDL_BUTTON_RIGHT:
						right_clic(event.button.x, event.button.y);
						break;
					case SDL_BUTTON_LEFT:
						left_clic(event.button.x, event.button.y);
						break;
					case SDL_BUTTON_WHEELDOWN:
						switch_coll();
						break;
					case SDL_BUTTON_WHEELUP:
						switch_coll();
						break;					
				}
				break;
			//~ case SDL_MOUSEMOTION:
				//~ m_static.display_collisions(&m_window);
				//~ m_window.blit_square(event.motion.x, event.motion.y, m_curr_coll);
				//~ m_window.flip_screen();	
				//~ break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_s:
						save();
						break;
					case SDLK_ESCAPE:
						leave();
						break;
					case SDLK_r:
						m_static.reset();
						refresh_screen();
						break;
					default:
						break;
				}
		}
	}	

}


void Editor::switch_coll()
{
	switch (m_curr_coll) {
	case NO_COLL:
		m_curr_coll = DOWN_COLL;
		break;
	case DOWN_COLL:
		m_curr_coll = FULL_COLL;
		break;
	case FULL_COLL:
		m_curr_coll = CLIMB_COLL;
		break;
	case CLIMB_COLL:
		m_curr_coll = NO_COLL;
	default:
		break;
	}
}



void Editor::right_clic(uint32_t x, uint32_t y)
{
	uint32_t x_prec = x, y_prec = y;
	uint32_t phase = 0;
	SDL_Event event;
	write_square(x, y);
	while (!m_leave){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				leave();
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_RIGHT){
					m_static.display_collisions(&m_window);
					refresh_ligne(x, y, x_prec, y_prec);
					write_ligne(x, y, event.button.x, event.button.y);
					m_window.flip_screen();
					return;
				}
				break;
			case SDL_MOUSEMOTION:
				if (phase > 5){
					refresh_ligne(x, y, x_prec, y_prec);
					draw_ligne(x, y, event.button.x, event.button.y);
					m_window.flip_screen();
					phase = 0;
					x_prec = event.button.x;
					y_prec = event.button.y;
				}
				else {
					phase++;
				}
				break;
			
		}
	}
}

void Editor::left_clic(uint32_t x, uint32_t y)
{
	SDL_Event event;
	write_square(x, y);
	while (!m_leave){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				leave();
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					return;
				break;
			case SDL_MOUSEMOTION:
				write_square(event.motion.x, event.motion.y);
				break;
		}
	}
}

void Editor::refresh_screen()
{
	m_static.display_collisions(&m_window);
	m_window.flip_screen();
}

void Editor::save()
{
	m_static.save();
}

void Editor::write_square(uint32_t x, uint32_t y)
{
	m_static.update_square(x / SQUARE_SIZE, y / SQUARE_SIZE, m_curr_coll);
	m_window.blit_square(x -  (x % SQUARE_SIZE), y -  (y % SQUARE_SIZE), m_curr_coll);
	m_window.flip_screen();
}

void Editor::draw_ligne(float x, float y, float X, float Y)
{
	float i = x , j = y, a = (Y-y)/(X-x);
	if (a < 0)
		a = -a;
	if (a < 1) {
		if (x < X){
			i = x; j = y;
		}
		else {
			i = X; j = Y; X = x; Y = y;
		}
		a = (Y-j)/(X-i);
		for (; i < X; i += SQUARE_SIZE) {
			j+= a * SQUARE_SIZE;
			m_window.blit_square(i , j, m_curr_coll);
		}
	}
	else {
		if (y < Y){
			i = x; j = y;
		}
		else {
			i = X; j = Y; X = x; Y = y;
		}
		a = (X-i)/(Y-j);
		for (; j < Y; j += SQUARE_SIZE) {
			i+= a * SQUARE_SIZE;
		m_window.blit_square(i , j , m_curr_coll);
		}	
	}	
}

void Editor::write_ligne(float x, float y, float X, float Y)
{
	float i = x , j = y, a = (Y-y)/(X-x);
	if (a < 0)
		a = -a;
	if (a < 1) {
		if (x < X){
			i = x; j = y;
		}
		else {
			i = X; j = Y; X = x; Y = y;
		}
		a = (Y-j)/(X-i);
		for (; i < X; i += SQUARE_SIZE) {
			j+= a * SQUARE_SIZE;
			write_square(i, j);
		}
	}
	else {
		if (y < Y){
			i = x; j = y;
		}
		else {
			i = X; j = Y; X = x; Y = y;
		}
		a = (X-i)/(Y-j);
		for (; j < Y; j += SQUARE_SIZE) {
			i+= a * SQUARE_SIZE;
			write_square(i, j);
		}	
	}
}

void Editor::refresh_ligne(float x, float y, float X, float Y)
{
	float i = x , j = y, a = (Y-y)/(X-x);
	if (a < 0)
		a = -a;
	if (a < 1) {
		if (x < X){
			i = x; j = y;
		}
		else {
			i = X; j = Y; X = x; Y = y;
		}
		a = (Y-j)/(X-i);
		for (; i < X; i += SQUARE_SIZE) {
			j+= a * SQUARE_SIZE;
			m_static.display_square(&m_window, i / SQUARE_SIZE, j / SQUARE_SIZE);
		}
	}
	else {
		if (y < Y){
			i = x; j = y;
		}
		else {
			i = X; j = Y; X = x; Y = y;
		}
		a = (X-i)/(Y-j);
		for (; j < Y; j += SQUARE_SIZE) {
			i+= a * SQUARE_SIZE;
			m_static.display_square(&m_window, i / SQUARE_SIZE, j / SQUARE_SIZE);
		}	
	}
}


void Editor::leave()
{
	m_leave = true;
}

