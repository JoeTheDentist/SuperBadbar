#include "AnimGrid.h"

#include "Grid.h"
#include "GridsContainer.h"

using namespace std;

AnimGrid::AnimGrid(string anim_name)
{
	m_grid = GridsContainer::GetInstance()->createGrid(anim_name);
	setPictures(0);
	m_curr = 0;
}

AnimGrid::~AnimGrid()
{

}

Surface *AnimGrid::curr_pic()
{
	return m_grid->getImage(m_picToDisplay.at(m_curr));
}

void AnimGrid::next_pic()
{
	m_curr++;
	m_curr %= m_picToDisplay.size();
}

void AnimGrid::set_rect(Rect &pos)
{
	pos.h = curr_pic()->h();
	pos.w = curr_pic()->w();
}

void AnimGrid::set_img(int i)
{
	m_curr = i%m_picToDisplay.size();
}

void AnimGrid::setPictures(int a, int b, int c, int d, int e, int f)
{
	m_picToDisplay.clear();
	m_picToDisplay.push_back(a);
	if (b != -1) {
		m_picToDisplay.push_back(b);
	}
	if (b != -1) {
		m_picToDisplay.push_back(c);
	}
	if (d != -1) {
		m_picToDisplay.push_back(d);
	}
	if (e != -1) {
		m_picToDisplay.push_back(e);
	}
	if (f != -1) {
		m_picToDisplay.push_back(f);
	}
}

bool AnimGrid::interruptable()
{
	return true;
}

bool AnimGrid::deletable()
{
	return false;
}
