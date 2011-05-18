/**
 * 	@file random_generator.h
 * 	@brief Header de la classe Random_generator
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */



/**
 * 	@class Random_generator
 * 	@brief Classe abstraire generant des nombres aleatoires
 *
 *	Fournit des lois uniformes pour des entiers et reels
 */
class Random_generator {
	
	/*!
	*	@brief Destructeur purement virtuel
	*/
	virtual ~Random_generator() = 0;
	
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
	*	@brief Genere un double avec une loi uniforme entre min et max
	*	@param min La borne inferieure
	*	@param max La borne superieure
	*/	
	static double drand(double min, double max);
	
	/*!
	*	@brief Genere un int avec une loi uniforme entre min et max
	*	@param min La borne inferieure
	*	@param max La borne superieure
	*/	
	static int irand(int min, int max);	
	
};
