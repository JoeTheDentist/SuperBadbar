#ifndef _COLLISION_MATRIX_
#define _COLLISION_MATRIX_

#define SIZE_SQUARE 5

#include <string>



class Collision_matrix {
private:
	size_t m_height;			/* Hauteur de la grille de collision */
	size_t m_weight;			/* Largeur de la grille de collision */
	uint32_t **m_matrix;		/* Grille de collision */
public:
	Collision_matrix();								/* Constructeur par défaut, forme une grille vide */
	Collision_matrix(size_t weight, size_t height);	/* Constructeur en ne donnant que la taille (la grille est remplie de 0)*/
	Collision_matrix(std::string file_name);		/* Constructeur en chargeant un fichier */
	~Collision_matrix();							/* Destructeur */
	void save(FILE *file);							/* Sauvegarde de la grille dans un fichier */
};

#endif