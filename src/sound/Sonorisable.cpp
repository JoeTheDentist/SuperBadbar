/**
 * 	@file sonorisable
 * 	@brief Header de la classe Sonorisable
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include "Sonorisable.h"

Sonorisable::Sonorisable()
{

}

Sonorisable::~Sonorisable()
{

}

void Sonorisable::prepare_sound(std::string sound)
{
	m_sounds_to_play.push(sound);
}

bool Sonorisable::no_more_sounds()
{
	return m_sounds_to_play.empty();
}

std::string Sonorisable::get_next_sound()
{
	return m_sounds_to_play.top();
}

void Sonorisable::pop_sound()
{
	m_sounds_to_play.pop();
}

