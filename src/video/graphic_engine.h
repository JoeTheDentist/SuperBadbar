/**
 * 	@file graphic_engine.h
 * 	@brief Header de la classe Graphic_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 
#ifndef _GRAPHIC_ENGINE_
#define _GRAPHIC_ENGINE_

class Camera;
class Babar;
class Static_data;

/**
 * 	@class Graphic_engine
 * 	@brief Moteur graphique 2D du jeu
 *
 */
class Graphic_engine {
private:
	Camera *m_camera;

public:
	/**
	 * 	@brief Constructeur
	 */
	Graphic_engine();

	/**
	 * 	@brief Destructeur
	 */
	~Graphic_engine();


	/**
	 * 	@brief Initialise le moteur graphique
	 */
	void init_graphic_engine(Babar *babar);


	/**
	 * 	@brief Accesseur
	 *	@return Un pointeur vers la camera
	 */
	Camera *get_camera();

	/**
	 * 	@brief Mise à jour du moteur graphique
	 *	
	 *	Met à jour la position de la camera
	 */
	void update(Static_data *static_data);
	
	
	/**
	 * 	@brief 
	 */

	/**
	 * 	@brief 
	 */

	/**
	 * 	@brief 
	 */


};


#endif
