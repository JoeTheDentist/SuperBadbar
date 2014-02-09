/**
 * @file csr.h
 * @brief Classe CSR
 *
 * @author CIMON Lucas & MOREL Benoit
 * @date 5 octobre 2010
 */
#ifndef _DEF_H_CSR
#define _DEF_H_CSR

#include "vector.h"

#include <string>

class MatLC;

/*! \class CSR
 * \brief Classe représentant une matrice creuse réelle de dimension 2
 * sans lignes ni colonnes nulles.
 *
 * On choisit le modèle de représentation Compressed Sparse Row (CSR)
 * en utilisant 3 vecteurs:
 * - AA les éléments non nuls de la matrice lus de gauche à droite puis de bas en haut
 * - JA les indices de ligne des éléments de AA
 * - IA les rangs des premiers éléments non nuls de chaque ligne ; IA[height] == JAA_size
 *
 * 	Les matrices sont chargées et traduites au format CSR à partir de fichiers
 * au format MMEF (Matrix Market Exchange Formats) par le constructeur.
*/
class CSR
{
private:
    unsigned int width, height, JAA_size;
    double *AA;
    unsigned int *JA;
    unsigned int *IA;

    void byebye();

    // Analyseur de fichier-matrice
    static bool read_separator (unsigned int &index, std::string line);
    static bool read_uint (unsigned int &index, std::string line, unsigned int &res);
    static bool read_d (unsigned int &index, std::string line, double &res);
    enum FileError {NO, OPEN, HEADER, LINE, NO_CONTENT, NO_SORT};
    FileError reader (const char* filename);

public:
    /*!
    \brief Constructeur de base
    */
    CSR();

    /*!
    \brief Constructeur de matrice identité
    \param n la taille de la matrice
    */
    CSR (unsigned int n);

    /*!
    \brief Constructeur de copie
    \param c matrice modèle
    */
    CSR (const CSR &c);

    /*!
    \brief Destructeur

    Libère AA, JA & IA
    */
    ~CSR();

    /*!
    \brief Chargement a partir d'un fichier

    	Construit une matrice CSR à partir d'un fichier Matrix Market Coordinate Format.
    	Ne fonctionne que si la description de la matrice est ordonnée (en lignes puis colonnes)
    	Le fichier peut n'indiquer que les coefficients non nuls, sans préciser de valeur : par défaut, on choisit 1.f.
    \param filename
    */
    bool load (const char* filename);

    /*!
    \brief Constructeur utilisé par matLC: construit la matrice CSR à partir de ses attributs
    \param w largeur
    \param h hauteur
    \param jsize nombre d'éléments non nuls
    \param aa vecteur AA
    \param ja vecteur JA
    \param ia vecteur IA
    */
    CSR (unsigned int w, unsigned int h, unsigned int jsize, double *aa, unsigned int *ja, unsigned int *ia);

    CSR (MatLC *matLC);

    /*!
    \brief Opérateur d'affectation
    */
    CSR& operator= (const CSR &c);

    /*!
    \brief Accesseur
    \return La largeur de la matrice de la matrice
    */
    unsigned int get_width() const
    {
        return width;
    }

    /*!
    \brief Accesseur
    \return La hauteur de la matrice de la matrice
    */
    unsigned int get_height() const
    {
        return height;
    }

    /*!
    \brief Accesseur
    \return Le nombre de valeurs non nulles dans *this
    */
    unsigned int get_nnz() const
    {
        return JAA_size;
    }

    /*!
    \brief Accesseur

    	Attention: la premiere ligne a pour indice 0
    	Attention: la premiere colonne a pour indice 0
    \return Le coefficient de la ieme ligne et jeme colonne
    */
    double get_coeff (unsigned int i, unsigned int j) const;

    /*!
    \brief Affiche la matrice sous format creux
    */
    void display_csr() const;

    /*!
    \brief Affiche la matrice sous format plein
    */
    void display_full() const;

    /*!
    \brief Opérateur binaire de multiplication
    \return Produit de la matrice par le scalaire
    */
    CSR operator* (const double d) const;

    CSR operator*= (const double d)
    {
        return (*this = *this * d);
    }

    /*!
    \brief Multiplication de matrices

    	Remarque: la fonction convertit les matrices au format matLC
    	(cout en nnz(A)+nnz(B)), les multiplie (cout en nnz(A)^2*nnz(B)/n^2)
    	puis reconvertit le résultat en CSR (cout en nnz(C)

    \param mat matrice à multiplier
    \return Produit de la matrice par la matrice mat
    */
    CSR operator* (const CSR &mat) const;

    /*!
    \brief Opérateur binaire de multiplication matrice * vecteur

    	L'opération a un coup proportionnel au maximum du nombre d'éléments
    	non nuls de la matrice et de la taille du vecteur
    \return Le produit de la matrice et du vecteur passé en paramètre.
    	En cas de tailles non compatibles, retourne un vecteur nul.
    \param v : vecteur facteur
    */
    Vector operator* (const Vector& v) const;

    /*!
    \brief Opérateur binaire de multiplication puis d'addition

    	L'opération a un coup proportionnel au maximum du nombre d'éléments
    	non nuls de la matrice et de la taille du vecteur
    \return Ax+b ou A est la matrice CSR appelant la methode
    	En cas de tailles non compatibles, retourne un vecteur nul.
    \param x : vecteur facteur
    \param b : vecteur terme
    */
    Vector mult_add (Vector x, Vector b) const;

    /*!
    \brief Calcule la plus grande valeur propre

    	Utilise l'algorithme de la puissance iteree.
    	ATTENTION : La matrice doit etre symetrique.
    \return La plus grande valeur propre de *this
    \param  epsilon le parametre de precision de l'algorithme
    */
    double puiss_iter (double epsilon) const;

    /*!
    \brief Transforme la matrice en sa transpose

    	L'opération a un coup proportionnel au maximum du nombre d'éléments
    	non nuls de la matrice et de la taille du vecteur
    */
    CSR	transpose() const;

    /*!
    \brief Opérateur binaire d'addition

    	Le cout est linéaire en fonction du nombres d'éléments non nuls des paramètres.
    \param m matrice terme
    */
    CSR operator+ (const CSR &m) const;

    /*!
    \brief Opérateur d'addition assignement

    	Appelle operator+.
    \param m matrice terme
    */
    CSR operator+= (const CSR &m)
    {
        return (*this = (*this) + m);
    }

    /*!
    \brief Résolution du système Ax = b

    	Cette fonction utilise la méthode du gradient bi-conjugué, avec I pour matrice de precondition.
    	Elle fonctionne aussi pour les matrices non-symetriques

    	Elle s'arrete lorsque |Ax-b| < \em epsilon, auquel cas on est sur d'avoir la bonne solution, ou après \em max_iter itération (pour éviter une boucle infinie). Dans ce cas, un warning est alors affiché dans la sortie d'erreur standard.

    	Source de l'algorithme: http://fr.wikipedia.org/wiki/M%C3%A9thode_du_gradient_biconjugu%C3%A9
    \param b le vecteur membre du systeme
    \param epsilon la precision du resultat
    \param max_iter le nombre maximum d'itérations
    \return le vecteur x solution
    */
    Vector resoudre_systeme_lineaire (Vector b, double epsilon, unsigned int max_iter = 500) const;

    /*!
    \brief Estimation d'un couple (valeur propre, vecteur propre)

    \param lambda valeur propre
    \param v vecteur propre
    \param epsilon la precision du resultat
    \param max_iter le nombre maximum d'itérations
    \return un booléen indiquant si tout s'est bien passé
    */
    bool iteration_de_rayleigh (double &lambda, Vector &v, double epsilon, unsigned int max_iter = 500) const;

    /*!
    \brief Décomposition QR: Q orthogonale et R triangulaire INFERIEURE

    	Travaille en place : la matrice est transformée en la matrice R de l'algorithme
    \return Q
    */
    CSR decompoQR();

    void changerEn (MatLC *matlc);

    /*!
    \brief Retourne la matrice correspondante au format MatLC

    	Le cout en temps est un O(nnz)
    \return la matrice au format MatLC
    */
    MatLC *conversion_MatLC() const;


    /*!
    \brief Supprime les lignes remplies uniquement de zéros
    */
    void supprEmptyLines();

    /*!
    \brief Met une matrice sous forme stochastique : supprime ses coefficients
    diagonaux et divise chaque coefficient par la somme de la colonne à
    laquelle il appartient.
    */
    void stochastiser();

    /*!
    \brief Algorithme défini dans googleEigenvector.pdf

    	REQUIERT que la matrice soit colonne-stochastique
    \return un vecteur propre
    */
    Vector googleEigenVector (double m, double epsilon) const;

};




#endif
