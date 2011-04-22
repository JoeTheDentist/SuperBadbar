/**
 * 	@file triggerable.h
 * 	@brief header de la classe Triggerable
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date avril 2011
 *
 */

#ifndef _BABAR_TRIGGERABLE_H_
#define _BABAR_TRIGGERABLE_H_

#include <string>
#include "../video/surface.h"

class Analyser;

/**
 * 	@class Triggerable
 * 	@brief Classe representant un evenement declenchable
 *
 *	Cet evenement doit etre etre declenche depuis l'exterieur (par un trigger 
 *	typiquement). 
 *	Il possede un champ nature, une position optionnelle et un texte optionnel.
 *	Ces champs sont lus par un analyser. Le fichier ouvert est de type:
 *		#nature# nature
 *		#x# x
 *		#y# y
 *		#text# "text entre guillements"
 *		#endtriggerable#
 *	nature est obligatoire et #endtriggerable# aussi (et doit etre a la fin)
 *
 *	
 *
 */
class Triggerable {
protected:
	int m_x;
	int m_y;
	std::string m_nature;
	std::string m_text;
public:
	
	/**
	 * 	@brief Constructeur
	 *	@param analyser l'analyser positionne juste avant un triggerable
	*/
	Triggerable(Analyser &analyser);

	/**
	 * 	@brief Destructeur
	*/
	virtual ~Triggerable();

	/**
	 * 	@brief Déclenche l'événement
	*/
	virtual void start();

protected:
	/*!
	* @brief Apparition d'un monstre
	* 
	* Le champ nature vaut "monster"
	* Les champs de position indiquent la position d'apparition du monstre
	* Le champ text indique le nom du monstre a ajouter
	*/
	void process_monster();

};


#endif
