/**
 * Description: La classe Analyser sert à lire des fichiers et à les interpréter
 * Utilisation: Utiliser open pour ouvrir un fichier.
 * 		L'interpréter avec les méthodes appropriées
 *		Le fermer avec close
 * Fonctionnement: 	Lors de la lecture du fichier, m_current représente le prochain caractère à analyser
 *			Il est lu à chaque fois lu à l'avance par convention
**/


#ifndef _ANALYSER_
#define _ANALYSER_

#include <string>
#include "sprites.h"
#include "statics.h"
#include "globals.h"



class Analyser {

private:
	bool m_opened;
	FILE * m_file;
	char m_current;

public:
	Analyser();					/* constructeur */
	~Analyser();					/* destructeur */
	uint32_t open(std::string file);		/* ouvre le fichier nommé file */
	uint32_t close();				/* ferme le fichier ouvert */
	void find_string(std::string str);		/* positionne le curseur de m_file après la première occurence de str à partir du début du fichier.
							Si la chaine n'est pas trouvée, le curseur est positionné à la fin du fichier */
	void jump_separators();				/* Saute les espaces, les retours à la ligne et les passages commentés (c'est-à-dire précédés de "//") */
	void read_monster(Monster *monster);		/* Met à jour (*monster) en fonction des données lues dans le fichier */
	void fill_statics();


};






#endif
