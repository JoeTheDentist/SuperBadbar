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

#define STATICS_DIR "../pic/statics/"
#define COLL_EXT ".col"
#define PICS_EXT ".bmp"



class Analyser {

private:
	bool m_opened;
	FILE * m_file;
	char m_current;

public:
	Analyser();							/* constructeur */
	~Analyser();						/* destructeur */
	uint32_t open(std::string file);	/* ouvre le fichier nommé file */
	uint32_t close();					/* ferme le fichier ouvert */
	void find_string(std::string str);	/* positionne le curseur de m_file après la première occurence de str à partir du début du fichier.
										Si la chaine n'est pas trouvée, le curseur est positionné à la fin du fichier */
	void jump_separators();				/* Saute les espaces, les retours à la ligne et les passages commentés (c'est-à-dire précédés de "//") */

	void fill_statics();
	void fill_collision_matrix(uint32_t **matrix); /* rempli matrix des collisions dues aux statics dans le fichier lu */
    int nb_monsters();							/* Renvoie le nombre de monstres différents */
    void fill_monsters_pics(int nb_monsters); 	/* Charge les images des monstres dans curr_lvl */
    void fill_monsters(Analyser * analyser);  	/* Remplis la matrice de curr_lvl */
    void fill_monsters_2(uint32_t *life, bool *fire, uint32_t *speed, uint32_t type);
};






#endif
