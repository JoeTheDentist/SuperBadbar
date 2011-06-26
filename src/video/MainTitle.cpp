#include "MainTitle.h"
#include "../video/SurfaceText.h"
#include "../video/SurfaceUniform.h"
#include "../video/SurfaceFrame.h"
#include "../video/Camera.h"
#include "../video/GraphicEngine.h"
#include "../util/globals.h"

MainTitle::MainTitle(std::string title):
	m_surface(NULL),
	m_surface_background(NULL),
	m_title(title),
	m_y(MAIN_TITLE_Y),
	m_size(MAIN_TITLE_SIZE),
	m_offset(MAIN_TITLE_OFFSET)
{
	recompute_surface();
	recompute_pos();
}

MainTitle::~MainTitle()
{
	delete m_surface;
}

void MainTitle::update()
{
	m_offset -= (m_offset / 3) + 1;
	if (m_offset <= 0)
		m_offset = 0;
	else {
		recompute_surface();
		recompute_pos();
	}
}

void MainTitle::display(Camera *camera)
{

	camera->display_picture(m_surface_background, &m_posbackground, true);
	camera->display_picture(m_surface, &m_pos, true);
}

void MainTitle::recompute_surface()
{
	delete m_surface;
	delete m_surface_background;
	m_surface = new SurfaceText(m_title, m_size + m_offset, MAIN_TITLE_R, MAIN_TITLE_G, MAIN_TITLE_B);
	recompute_pos();
	m_surface_background = new SurfaceUniform(m_posbackground.w, m_posbackground.h,
				MAIN_TITLE_BACK_R, MAIN_TITLE_BACK_G, MAIN_TITLE_BACK_B);
	m_surface_background->set_alpha(MAINT_TITLE_BACKGROUND_ALPHA);
}

void MainTitle::recompute_pos()
{
	Camera *camera = gGraphics->get_camera();
	m_pos.w = m_surface->w();
	m_pos.h = m_surface->h();
	m_pos.x = (camera->width() - m_pos.w) / 2;
	m_pos.y = m_y - m_pos.h;
	m_posbackground.w = m_pos.w + MAIN_TITLE_BACKGROUND_OFFSET_W * 2;
	m_posbackground.h = m_pos.h + MAIN_TITLE_BACKGROUND_OFFSET_H * 2;
	m_posbackground.x = (camera->width() - m_posbackground.w) / 2;
	m_posbackground.y = m_pos.y - MAIN_TITLE_BACKGROUND_OFFSET_H;
}
