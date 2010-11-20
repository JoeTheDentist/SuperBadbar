/**
 * WARNING : classe à refaire
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



#define COLL_EXT ".col"
#define PICS_EXT ".bmp"

class Statics;
class Static_data;
class Dynamic_data;

class Analyser {

private:
	bool m_opened;
	FILE * m_file;


	

public:
	/*!
	* @brief Constructeur par défaut
	*/
	Analyser();

	/*!
	* @brief Destructeur par défaut
	*/
	~Analyser();

 	/*!
	* @brief ouvre le fichier nommé file
	* @param file nom du fichier à ouvrir
	* @return renvoie 1 si l'ouverture est un succès, 0 sinon
	*/
	uint32_t open(std::string file);

  	/*!
	* @brief ferme le fichier ouvert
	*/
	void close();	

   	/*!
	* @brief Saute les séparateurs dans le fichier ouvert
	* 
	* Un séparateur est un espace, un retour à la ligne ou une ligne suivant //
	*/
	void jump_separators();	
	
	/*!
	* @brief Positionne le curseur après la première occurence de str à partir du début du fichier
	*
	* Si la chaine n'est pas trouvée, le curseur est positionné à la fin du fichier
	*
	* @param str La chaine cherchée
	*/
	void find_string(std::string str);
	
	/*!
	* @brief Lit et renvoie le prochain int du fichier, en sautant les séparateurs
	* 
	* @return l'int lu
	*/
	int read_int();
	
	/*!
	* @brief Lit et renvoie le prochain uint32_t du fichier, en sautant les séparateurs
	* 
	* @return l'uint32_t lu
	*/	
	uint32_t read_uint32_t();

	/*!
	* @brief Lit dans le fichier la section suivant #Statics# et l'ajout à la liste globale curr_statics
	*/
	void fill_statics(Static_data *static_data);	
	
	/*!
	* @brief Lit dans m_file la section #Statics# et remplit la matrix de collisions matrix
	*/
	void fill_collision_matrix(uint32_t **matrix); 
	
	/*!
	* @brief Renvoie le nombre de monstres différents dans le fichier ouvert 
	* @return   le nombre de monstres différents dans le fichier ouvert
	*/               
    int nb_monsters();
	
	/*!
	* @brief Charge les images des monstres dans static_data à partir de la section #Monsters#
	* @param nb_monsters le nombre de monstres du niveau
	* @param static_data un pointeur vers la classe qui va stocker les images chargées
	*/
    void fill_monsters_pics(int nb_monsters, Static_data *static_data);
	
	/*!
	* @brief Fonction un peu chelou (à refaire)
	*/
    void fill_monsters(Analyser * analyser, Static_data *static_data, Dynamic_data *dynamic_data);  	/*  */
												/* analyser est un deuxieme analyser qui doit etre ouvert */
    void fill_monsters_2(uint32_t *life, bool *fire, uint32_t *speed, uint32_t type);
};






#endif
