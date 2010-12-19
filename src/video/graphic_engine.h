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
class Talks;


/**
 * 	@class Graphic_engine
 * 	@brief Moteur graphique 2D du jeu
 *
 */
class Graphic_engine {
private:
	Camera *m_camera;
	Talks *m_talks;
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
	 *	@todo On a juste besoin du picture_container, qui doit faire partie de graphic_engine..
	 */
	void init_graphic_engine(Babar *babar, Static_data *static_data);


	/**
	 * 	@brief Mise à jour du moteur graphique
	 *	
	 *	Met à jour la position de la camera
	 */
	void update(Static_data *static_data);


	/**
	 * 	@brief Accesseur
	 *	@return Un pointeur vers la camera
	 */
	Camera *get_camera();


	
	/**
	 * 	@brief Accesseur
	 *	@return Un pointeur vers le gestionnaire de dialogues
	 */
	Talks *get_talks();
	
	
	/**
	 * 	@brief 
	 */

	/**
	 * 	@brief 
	 */


};


#endif
