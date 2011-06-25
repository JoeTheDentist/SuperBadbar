/**
 * 	@file sonorisable
 * 	@brief Header de la classe Sonorisable
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SONORISABLE_
#define _SONORISABLE_

#include <stack>
#include <string>

class Sound;


/*!
*	@class Sonorisable
*	@brief Classe mère de tout objet pouvant produire un son
*	
*	Utilisation par la classe fille: \n
*	- Utiliser prepare_sound pour chaque son à jouer \n
*	- Appeler le play_sounds de sound_engine
*	pour jouer les sons préparés
*
*	Utilisation par le sound_engine:\n
*	Tant qu'il y a des sons, jouer le prochain son et poper
*/
class Sonorisable {
protected:
	std::stack<std::string> m_sounds_to_play;
public:
	/*!
	 *	@brief Constructeur par défaut
	*/
	Sonorisable();

	/*!
	 *	@brief Destructeur
	*/
	~Sonorisable();

	/*!
	 *	@brief Prepare un son à jouer au prochain passage de sound_engine
	 *	@param sound Le son à jouer
	*/
	void prepare_sound(std::string sound);

	/*!
	 *	@brief Accesseur
	 *	@return Vrai s'il n'y a plus de sons à jouer
	*/
	bool no_more_sounds();

	/*!
	 *	@brief Accesseur
	 *	@return Le prochain son à jouer
	*/
	std::string get_next_sound();
	
	/*!
	 *	@brief Supprime le premier son des sons à jouer
	*/
	void pop_sound();
};


#endif
