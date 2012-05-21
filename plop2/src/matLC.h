/**
 * @file matLC.h
 * @brief Classe matLC
 * @author CIMON Lucas & MOREL Benoit
 * @date 14 novembre 2010
 */

#ifndef _MATLC_
#define _MATLC_

#include <string>
#include <list>



/*! \class MatLC
 * \brief Implemention des matrices creuses avec tableau de listes chainees
 * 
 * Attention: la classe n'est pour l'instant utilisable qu'à partir de la classe CSR
 * elle ne servira a priori qu'à la decompositionQR de CSR
 *
 * Remarque: les erreurs machines introduisent des coefficients très faibles mais non nuls
 * dans la décomposition QR, ce qui pose problème pour notre structure de matrices creuses. 
 * Pour éviter celà, on définit une constante epsilon telle que tout élément inférieur à 
 * epsilon est considéré comme nul dans nos calculs.
 */
class MatLC {
public:
	/*!
	 * \struct maillon
	 * Représente un coefficient non nul de la matrice.
	 */
	struct maillon {
		double val;
		unsigned int col;
	};
	
private:
	unsigned int width; 		/* Largeur de la matrice */
	unsigned int height; 		/* Hauteur de la matrice */
	std::list<struct maillon>* ligne;	/* Tableau des listes chainées représentant les lignes */
	double epsilon; /* precision des coefficients (calculé comme le min des coefficients à la construction / rapport_coeff_precision */
	static const double rapport_coeff_precision;

	void incr_coeff_intern(unsigned int lig, unsigned int col, double x);
	void set_coeff_intern(unsigned int lig, unsigned int col, double x);

public:
	
	MatLC(const MatLC& mat);

 	/*!
	 * \brief Constructeur: construit la matrice identite de taille n
	 * \param n  Taille de la matrice
	*/
	MatLC(unsigned int n);

  	/*!
	 * \brief Constructeur: construit une matrice nulle de hauteur i et de largeur j
	 * \param i  hauteur
	 * \param j  largeur
	*/
	MatLC(unsigned int i, unsigned int j);

	void calcule_CSR(double **aa, unsigned int **ja, unsigned int **ia, unsigned int *w, unsigned int *h, unsigned int *j_size);

	/*!
	 * \brief Constructeur appelé par CSR
	 * \param AA 
	 * \param IA 
	 * \param JA 
	 * \param w largeur 
	 * \param h hauteur
	*/
	MatLC(double *AA, unsigned int *JA, unsigned int *IA, unsigned int w, unsigned int h);

	/*!
	 * \brief Destructeur
	*/
	~MatLC();


	MatLC& operator=(const MatLC &mat);


	/*!
	 * \brief Accesseur au coefficient de la ligne lig et de la colonne col de la matrice 
	 * \param lig ligne
	 * \param col colonne
	*/
	double get_coeff(unsigned int lig, unsigned int col);
	
	bool presque_nul(double d) ;
 
	/*!
	 * \brief Mutateur du coefficient de la ligne lig et de la colonne col de la matrice 
	 * Si x est nul alors on n'alloue pas (ou, selon les cas, on supprime) le maillon correspondant
	 * \param lig ligne
	 * \param col colonne
	 * \param x élément à muter
	*/	
	void set_coeff(unsigned int lig, unsigned int col, double x);
	
	/*!
	 * \brief Ajoute x au coefficient de la ligne lig et de la colonne col
	 * Attention: ne pas confondre avec set_coeff qui remplace la valeur par x
	 * \param lig ligne
	 * \param col colonne
	 * \param x élément à ajouter
	*/	
	void incr_coeff(unsigned int lig, unsigned int col, double x);
	
	/*!
	\brief Affichage de la matrice au format plein
	*/
	void display();	
	
	/*!
	\brief Transposée...
	\return la transposé
	*/
	MatLC *transpose();
	
	
	/*!
	\brief Effectue le produit de la matrice par B
	\param B matrice à multiplier
	\return le produit
	*/
	MatLC *produit(MatLC *B);
	
	/*!
	\brief calcule la trace de la matrice
	\return la trace de la matrice
	*/
	double trace();

	/*!
	\brief Décomposition QR: Q orthogonale et R triangulaire INFERIEURE

		Travaille en place : la matrice est transformée en la matrice R de l'algorithme
	\return Q
	*/		
	MatLC *decompoQR();
};


#endif
