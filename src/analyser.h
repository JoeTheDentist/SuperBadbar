#ifndef _ANALYSER_
#define _ANALYSER_

#include <string>

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
};






#endif