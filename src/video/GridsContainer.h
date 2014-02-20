#ifndef GRIDSCONTAINER_H
#define GRIDSCONTAINER_H

#include <map>
#include <string>

class Grid;

/**
 *	Container for grids;
 *	Singleton.
 */
class GridsContainer
{
public:
    /**
     *	Getter
     *	@return the instance of GridContainer
     */
    static GridsContainer *GetInstance();

    /**
     *	Frees the instance
     */
    static void Destroy();

    /**
     *	Create and get the wanted grid
     *	@param pathToImage: path to the image to use as a grid
     *	@return new grid of the given image
     */
    Grid *createGrid (std::string pathToImage);

private:
    static GridsContainer *s_instance;
    std::map<std::string, Grid*> m_grids;

    /**
     *	Ctor
     */
    GridsContainer();

    /**
     *	Dtor
     */
    ~GridsContainer();
};

#endif // GRIDSCONTAINER_H
