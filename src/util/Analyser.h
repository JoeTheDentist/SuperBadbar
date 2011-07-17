/**
 * 	@file analyser.h
 * 	@brief Header de la classe Analyser
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */






#ifndef _ANALYSER_
#define _ANALYSER_

#include <string>
#include <fstream>
#include <stdint.h>
#include <stack>

#define COLL_EXT ".col"
#define PICS_EXT ".png"

/**
 * 	@class Analyser
 * 	@brief Lit les fichiers
 *
 * Utilisation: Utiliser open pour ouvrir un fichier.
 * 				L'interpréter avec les méthodes appropriées
 *				Le fermer avec close
 * Fonctionnement: 	Lors de la lecture du fichier, m_current représente le prochain caractère �  analyser
 *				Il est lu �  chaque fois lu �  l'avance par convention
**/

class Analyser {

private:
	bool m_opened;
	std::ifstream *m_file;
	std::string m_filename;
	std::stack<std::streamoff> m_curs_stack;
public:
	/**
	* @brief Constructeur par défaut
	*/
	Analyser();

	/**
	* @brief Destructeur par défaut
	*/
	~Analyser();

 	/**
	* @brief ouvre le fichier nommé file
	* @param file nom du fichier �  ouvrir
	* @return renvoie vrai si l'ouverture est un succès, faux sinon
	*/
	bool open(std::string file);

  	/**
	* @brief ferme le fichier ouvert
	*/
	void close();

   	/**
	* @brief Saute les séparateurs dans le fichier ouvert
	*
	* Un séparateur est un espace, un retour �  la ligne ou une ligne suivant //
	* @warning non fonctionnelle sous windows
	*/
	void jump_separators();

	/**
	* @brief Positionne le curseur après la première occurence de str �  partir du début du fichier
	* @return vrai si la chaine a été trouvée
	* Si la chaine n'est pas trouvée, le curseur est positionné �  la fin du fichier.
	*
	* @param str La chaine cherchée
	*/
	bool find_string(std::string str);

	/**
	* @brief Positionne le curseur après la première occurence de str �  partir du curseur actuel
	* @return vrai si la chaine a été trouvée
	* Si la chaine n'est pas trouvée, le curseur est positionné �  la fin du fichier.
	*
	* @param str La chaine cherchée
	*/
	bool find_next_string(std::string str);

	/**
	* @return vrai si on est �  la fin d'une section (si le caractère suivant est un '!'
	* @warning non fonctionnelle sur windows (�  cause de jump_separators)
	*/
	bool end_of_section();

	/**
	* @brief Lit et renvoie le prochain int du fichier, en sautant les séparateurs
	* @return l'int lu
	*/
	int read_int();

	/**
	* @brief Lit et renvoie le prochain unsigned int du fichier, en sautant les séparateurs
	* @return l'unsigned int lu
	*/
	unsigned int read_unsigned_int();

	/**
	* @brief Lit et renvoie le prochain double du fichier, en sautant les séparateurs
	* @return le double lu
	*/
	double read_double();

	/**
	* @brief Lit et renvoie le prochain string du fichier (jusqu'au prochain espace), en sautant les séparateurs
	* @return le string lu
	*/
	std::string read_string();

	/**
	* @brief Lit la prochaine string entouree par un caractere (par ex # ou ")
	* @param delimitor Le caractere entourant la string a retrouver
	* @return La string sans le delimiteur
	*/
	std::string read_between_char(char delimitor);

	/**
	* @brief Lit et renvoie le prochain char du fichier
	* @return le char lu
	*/
	char read_char();

	/**
	*	@brief Sauvegarde la position du curseur actuelle dans une pile
	*/
	void push_curs();

	/**
	*	@brief Repositionne le curseur dans la valeur la plus haute de la pile
	*
	* 	(la pile est depilee)
	*/
	void pop_curs();

};






#endif
