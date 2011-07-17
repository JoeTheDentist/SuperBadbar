/**
 * 	@file sonorisable
 * 	@brief Header de la classe Sonorisable
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SONORISABLE_
#define _SONORISABLE_

#include <stack>
#include <string>

class Sound;


/**
*	@class Sonorisable
*	@brief Classe m√®re de tout objet pouvant produire un son
*
*	Utilisation par la classe fille: \n
*	- Utiliser prepare_sound pour chaque son √  jouer \n
*	- Appeler le play_sounds de sound_engine
*	pour jouer les sons pr√©par√©s
*
*	Utilisation par le sound_engine:\n
*	Tant qu'il y a des sons, jouer le prochain son et poper
*/
class Sonorisable {
protected:
	std::stack<std::string> m_sounds_to_play;
public:
	/**
	 *	@brief Constructeur par d√©faut
	*/
	Sonorisable();

	/**
	 *	@brief Destructeur
	*/
	~Sonorisable();

	/**
	 *	@brief Prepare un son √  jouer au prochain passage de sound_engine
	 *	@param sound Le son √  jouer
	*/
	void prepare_sound(std::string sound);

	/**
	 *	@brief Accesseur
	 *	@return Vrai s'il n'y a plus de sons √  jouer
	*/
	bool no_more_sounds();

	/**
	 *	@brief Accesseur
	 *	@return Le prochain son √  jouer
	*/
	std::string get_next_sound();

	/**
	 *	@brief Supprime le premier son des sons √  jouer
	*/
	void pop_sound();
};


#endif
