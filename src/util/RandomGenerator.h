/**
 * 	@file RandomGenerator.h
 * 	@brief Header de la classe RandomGenerator
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mai 2011
 *
 */



/**
 * 	@class RandomGenerator
 * 	@brief Classe abstraire generant des nombres aleatoires
 *
 *	Fournit des lois uniformes pour des entiers et reels
 */
class RandomGenerator
{
public:
    /**
    *	@brief Destructeur purement virtuel
    */
    virtual ~RandomGenerator() = 0;

    /**
    *	@brief Initialise le generateur de nombres aleatoires
    */
    static void init();

    /**
    *	@brief Genere un int avec une loi uniforme entre min et max
    *	@param min La borne inferieure
    *	@param max La borne superieure
    */
    static int irand (int min, int max);

    /**
    *	@brief Genere un float avec une loi uniforme entre min et max
    *	@param min La borne inferieure
    *	@param max La borne superieure
    */
    static float frand (float min, float max);

    /**
    *	@brief Genere un double avec une loi uniforme entre min et max
    *	@param min La borne inferieure
    *	@param max La borne superieure
    */
    static double drand (double min, double max);



    /**
    *	@brief Genere un double avec une loi normale de parametre mu et sigma
    *	@param mu La moyenne
    *	@param sigma La racine de la variance
    */
    static double rnorm (double mu, double sigma);

};
