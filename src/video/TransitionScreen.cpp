/**
 * 	@file TransitionScreen.cpp
 * 	@brief Implementation de la classe TransitionScreen
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "TransitionScreen.h"

#include "control/Keyboard.h"
#include "util/globals.h"
#include "util/repertories.h"
#include "video/Camera.h"
#include "video/GraphicEngine.h"
#include "video/Surface.h"
#include "video/SurfaceText.h"


TransitionScreen::TransitionScreen(std::string picture_path, std::string text1, std::string text2):
	m_skipable(false),
	m_ended(false),
	m_background(new Surface(PIC_TRANSITIONS_R + picture_path)),
	m_text1(new SurfaceText(text1)),
	m_text2(new SurfaceText(text2))
{
	m_pos_text1.x = (Constants::WINDOW_WIDTH - m_text1->w()) / 2;
	m_pos_text2.x = (Constants::WINDOW_WIDTH - m_text2->w()) / 2;
	m_pos_text1.y = (Constants::WINDOW_HEIGHT * 3) / 4;
	m_pos_text2.y = (Constants::WINDOW_HEIGHT * 3) / 4;
}

TransitionScreen::~TransitionScreen()
{
	delete m_background;
	delete m_text1;
	delete m_text2;
}

void TransitionScreen::update()
{
}

void TransitionScreen::display(Camera *camera)
{
	Rect pos;
	camera->display_picture(m_background, &pos, true);
	if (!m_skipable) {
		camera->display_picture(m_text1, &m_pos_text1, true);
	} else {
		camera->display_picture(m_text2, &m_pos_text2, true);
	}
	camera->flip_camera();
}

void TransitionScreen::wait_for_player()
{
	m_skipable = true;
	m_skipable = true;
	display(gGraphics->get_camera());
	gKeyboard->wait_for_any_key();
}

bool TransitionScreen::ended()
{
	return m_ended;
}
