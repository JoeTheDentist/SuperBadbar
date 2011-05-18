/**
 * 	@file random_generator.h
 * 	@brief Header de la classe Random_generator
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */


class Random_generator {
	/*!
	*	@brief Initialise le generateur de nombres aleatoires
	*/
	static void init();
	
	/*!
	*	@brief Genere un float avec une loi uniforme entre min et max
	*	@param min La borne inferieure
	*	@param max La borne superieure
	*/	
	static float frand(float min, float max);
	
	/*!
	*	@brief Genere un int avec une loi uniforme entre min et max
	*	@param min La borne inferieure
	*	@param max La borne superieure
	*/	
	static int irand(int min, int max);	
	
};
