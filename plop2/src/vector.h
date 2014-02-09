/*!
 * @file vector.h
 * @brief Classe Vector
 *
 * @author CIMON Lucas & MOREL Benoit
 * @date 5 octobre 2010
 */
#ifndef _DEF_H_VECTOR
#define _DEF_H_VECTOR


/*! \class Vector
 * \brief Vecteur de double
 *
 * La taille du vecteur peut varier.
 * Plusieurs opérations élémentaires sont implémentées sous forme de méthodes.
 */
class Vector
{

private:
    unsigned int n;	/*!< Taille */
    double *val;    /*!< Tableau des coordonnées */


public:
    /*!
     *  \brief Constructeur de vecteur vide
     */
    Vector();

    /*!
     * \brief Constructeur de vecteur rempli de 0
     * \param size taille du vecteur
     */
    Vector (unsigned int size);

    /*!
     * \brief Constructeur de vecteur rempli de valeurs aléatoires entre -1 et 1
     * \param size taille du vecteur
     * \param only_positive valeurs uniquement positives
     */
    Vector (unsigned int size, bool only_positive);

    /*!
     * \brief Constructeur de copie
     * \param v vecteur modèle
     */
    Vector (const Vector& v);

    /*!
     *  \brief Destructeur
     */
    ~Vector();


    /*!
    * \brief Opérateur d'affectation
    */
    void operator= (const Vector &v);

    /*!
     *  \brief Accesseur
     *  \param i indice de l'élément dans le vecteur.
     * Si négatif, accès à l'élément n + i.
     *  \return la ième valeur du vecteur
     */
    double& operator[] (int i);

    /*!
     *  \brief Accesseur constant
     *  \param i indice de l'élément dans le vecteur.
     * Si négatif, accès à l'élément n + i.
     *  \return la ième valeur du vecteur, l'infini si il n'y a pas d'index i.
     */
    double get (int i) const;

    /*!
     *  \brief Affiche le contenu du vecteur
     */
    void display() const;

    /*!
     *  \brief Accesseur
     *  \return La taille du vecteur
     */
    unsigned int size() const;

    /*!
     *  \brief Accesseur
     *  \return La norme euclidienne du vecteur
     */
    double norm() const;

    /*!
     *  \brief Modifie la taille du vecteur
     *  \param size taille souhaitée
     */
    void resize (unsigned int size);


    /*!
    * \brief Opérateur binaire d'addition
    * \return La somme des vecteurs
    */
    Vector operator+ (const Vector &v) const;

    /*!
    * \brief Opérateur binaire de soustraction
    * \return La différence des vecteurs
    */
    Vector operator- (const Vector &v) const;

    /*!
     * \brief Produit scalaire
     * \return <this|v>
    */
    double operator* (const Vector &v) const;

    /*!
    * \brief Opérateur binaire de multiplication
    * \return Produit terme à terme des vecteurs
    */
    Vector fwd_prod (const Vector &v);

    /*!
    * \brief Opérateur binaire de multiplication scalaire
    * \return Produit du vecteur par le scalaire
    */
    Vector operator* (const double d) const;

    /*!
    * \brief Opérateur de division
    * \return La division du vecteur par le scalaire
    */
    Vector operator/ (const double d) const;

    /*!
    * \brief Opérateur de division
    * \return La division du vecteur par le scalaire
    */
    Vector operator-() const;

    /*!
    * \brief Opérateur d'addition assignement
    * \return Une copie du vecteur incrémenté
    */
    Vector operator+= (const Vector &v);

    /*!
    * \brief Opérateur de soustraction assignement
    * \return Une copie du vecteur décrémenté
    */
    Vector operator-= (const Vector &v);

    /*!
    * \brief Opérateur de multiplication scalaire assignement
    * \return Une copie du vecteur multiplié
    */
    Vector operator*= (const double d);
};

#endif
