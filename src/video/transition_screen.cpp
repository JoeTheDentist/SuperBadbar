/**
 * 	@file transition_screen.cpp
 * 	@brief Implementation de la classe Transition_screen
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */
 
#include "transition_screen.h"
#include "../video/surface_text.h"
#include "../video/camera.h"
#include "../video/graphic_engine.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/keyboard.h"

	
Transition_screen::Transition_screen(std::string picture_path, std::string text1, std::string text2):
	m_skipable(false),
	m_ended(false),
	m_background(new Surface(PIC_TRANSITIONS_R + picture_path)),
	m_text1(new Surface_text(text1)),
	m_text2(new Surface_text(text2))
{
	m_pos_text1.x = (WINDOW_WIDTH - m_text1->w()) / 2;
	m_pos_text2.x = (WINDOW_WIDTH - m_text2->w()) / 2;
	m_pos_text1.y = (WINDOW_HEIGHT * 3) / 4;
	m_pos_text2.y = (WINDOW_HEIGHT * 3) / 4;
}

Transition_screen::~Transition_screen()
{
	delete m_background;
	delete m_text1;
	delete m_text2;
}
	
void Transition_screen::update()
{
}

void Transition_screen::display(Camera *camera)
{
	Rect pos;
	pos.x = 0;
	pos.y = 0;
	camera->display_picture(m_background, &pos, true);	
	if (!m_skipable) {
		camera->display_picture(m_text1, &m_pos_text1, true);	
	} else {
		camera->display_picture(m_text2, &m_pos_text2, true);	
	}
	camera->flip_camera();
}

void Transition_screen::wait_for_player()
{
	m_skipable = true;
	display(gGraphics->get_camera());
	gKeyboard->wait_for_any_key();
}

bool Transition_screen::ended()
{
	return m_ended;
}
