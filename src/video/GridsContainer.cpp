#include "GridsContainer.h"

#include "Grid.h"

GridsContainer *GridsContainer::s_instance = 0;

GridsContainer *GridsContainer::GetInstance()
{
	if (!s_instance)
	{
		s_instance = new GridsContainer();
	}
	return s_instance;
}

void GridsContainer::Destroy()
{
	delete s_instance;
	s_instance = 0;
}

Grid *GridsContainer::createGrid(std::string pathToImage)
{
	std::map<std::string, Grid*>::iterator it = m_grids.find(pathToImage);
	Grid *grid = 0;
	if (it == m_grids.end()) {
		grid = new Grid(pathToImage);
		m_grids.insert(std::pair<std::string, Grid*>(pathToImage, grid));
	} else {
		grid = (*it).second;
	}
	return grid;
}

GridsContainer::GridsContainer()
{

}

GridsContainer::~GridsContainer()
{
	std::map<std::string, Grid*>::iterator it;
	for (it = m_grids.begin(); it != m_grids.end(); it++) {
		delete it->second;
	}
}
