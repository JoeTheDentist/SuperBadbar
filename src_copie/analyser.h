/**
 * Description: La classe Analyser sert à lire des fichiers et à les interpréter
 * Utilisation: Utiliser open pour ouvrir un fichier.
 * 				L'interpréter avec les méthodes appropriées
 *				Le fermer avec close
 * Fonctionnement: 	Lors de la lecture du fichier, m_current représente le prochain caractère à analyser
 *				Il est lu à chaque fois lu à l'avance par convention
**/


#ifndef _ANALYSER_
#define _ANALYSER_

#include <string>



#define STATICS_DIR "../pic/statics/"
#define COLL_EXT ".col"
#define PICS_EXT ".bmp"

class Statics;
class Static_data;
class Dynamic_data;

class Analyser {

private:
	bool m_opened;
	FILE * m_file;
	


	void jump_separators();				/* Saute les espaces, les retours à la ligne et les passages commentés (c'est-à-dire précédés de "//") */

public:
	Analyser();							/* constructeur */
	~Analyser();						/* destructeur */
	uint32_t open(std::string file);	/* ouvre le fichier nommé file renvoie 1 si le fichier ne s'ouvre pas, 0 sinon*/
	uint32_t close();					/* ferme le fichier ouvert */
	void find_string(std::string str);	/* positionne le curseur de m_file après la première occurence de str à partir du début du fichier.
										Si la chaine n'est pas trouvée, le curseur est positionné à la fin du fichier */

	void fill_statics(Static_data *static_data);				/* Lit dans m_file la section #Statics# et l'ajoute à la liste globale curr_statics */
	void fill_collision_matrix(uint32_t **matrix); /* Lit dans m_file la section #Statics# et remplit la matrix de collisions matrix*/
    int nb_monsters();							/* Renvoie le nombre de monstres différents dans le fichier m_file*/
    void fill_monsters_pics(int nb_monsters, Static_data *static_data); 	/* Charge les images des monstres dans curr_lvl à partir de la section #Monsters#*/
												/* DOIT etre utilisé après nb_monsters */
    void fill_monsters(Analyser * analyser, Static_data *static_data, Dynamic_data *dynamic_data);  	/* Remplit la matrice des monstres de curr_lvl */
												/* analyser est un deuxieme analyser qui doit etre ouvert */
    void fill_monsters_2(uint32_t *life, bool *fire, uint32_t *speed, uint32_t type); 
};






#endif
