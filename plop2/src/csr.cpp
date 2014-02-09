#include "csr.h"

#include "utile.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include "matLC.h"


CSR::CSR() : width (0), height (0), JAA_size (0), AA (NULL), JA (NULL), IA (NULL) {}


CSR::CSR (unsigned int n) : width (n), height (n), JAA_size (n)
{
    AA = new double[n];
    JA = new unsigned int[n];
    IA = new unsigned int[n + 1];
    for (unsigned int i = 0; i < n; i++)
    {
        AA[i] = 1;
        IA[i] = i;
        JA[i] = i;
    }
    IA[n] = JAA_size;
}


CSR::CSR (const CSR &c) : width (c.width), height (c.height),
    JAA_size (c.JAA_size), AA (NULL), JA (NULL), IA (NULL)
{
    AA = new double[JAA_size];
    for (unsigned int i = 0; i < JAA_size; i++)
        AA[i] = c.AA[i];
    JA = new unsigned int[JAA_size];
    for (unsigned int i = 0; i < JAA_size; i++)
        JA[i] = c.JA[i];
    IA = new unsigned int[height + 1];
    for (unsigned int i = 0; i <= height; i++)
        IA[i] = c.IA[i];
}


void CSR::byebye()
{
    if (IA != NULL)
    {
        delete[] IA;
        IA = NULL;
    }
    if (JA != NULL)
    {
        delete[] JA;
        JA = NULL;
    }
    if (AA != NULL)
    {
        delete[] AA;
        AA = NULL;
    }
    width = 0;
    height = 0;
    JAA_size = 0;
}


CSR::~CSR()
{
    byebye();
}


bool CSR::load (const char* filename)
{
    byebye();
    FileError my_error = reader (filename);
//~ 	TRACE("width: " << width << " | height: " << height << " | JAA_size: " << JAA_size)
    if (!my_error)
        return true;

    std::string str_error = "Analyseur de fichier-matrice : ";
    switch (my_error)
    {
    case OPEN:
        str_error += "Impossible d'ouvrir le fichier";
        break;
    case HEADER:
        str_error += "En-tête erroné ou incomplet";
        break;
    case LINE:
        str_error += "Ligne incomplète";
        break;
    case NO_CONTENT:
        str_error += "Fichier incomplet";
        break;
    case NO_SORT:
        str_error += "Description non ordonnée";
        break;
    default:
        break;
    }
    TRACE_ (str_error)
    return false;
}


CSR::FileError CSR::reader (const char* filename)
{
    // Ouverture du fichier
    std::fstream file (filename);
    if ( !file )
        return OPEN;

    // Lecture des commentaires d'en-tête
    std::string line;
    getline (file, line);
    while (!file.eof() && line[0] == '%')
        getline (file, line);
    if (file.eof() )
        return NO_CONTENT;

    // Lecture du format de la matrice
    unsigned int str_index = 0;
    read_separator (str_index, line);
    if (!read_uint (str_index, line, width)
            || !read_separator (str_index, line)
            || !read_uint (str_index, line, height)
            || !read_separator (str_index, line)
            || !read_uint (str_index, line, JAA_size) )
        return HEADER;
    getline (file, line);
    str_index = 0;


    // Allocation mémoire
    AA = new double[JAA_size];
    JA = new unsigned int[JAA_size];
    IA = new unsigned int[height + 1];
    // On initialise IA avec des zéros à cause des lignes vides
    for (unsigned int i_row = 0; i_row <= height; i_row++)
        IA[i_row] = 0;

    // Insertion des valeurs
    unsigned int	i = 1, old_i = 0,
                    j = 1, old_j = 0,
                    i_JAA = 0;
    double value = 0.f;
    while ( !file.eof() )
    {
        read_separator (str_index, line);
        if (!read_uint (str_index, line, j)
                || !read_separator (str_index, line)
                || !read_uint (str_index, line, i) )
            return LINE;
        if (!read_separator (str_index, line)
                || !read_d (str_index, line, value) )
        {
            value = 1.f; // Si pas de valeur indiquée, matrices remplies de 1.f
        }
        else if (!value)
        {
            getline (file, line);
            str_index = 0;
            continue;
        }
        if (i_JAA == JAA_size)
            return HEADER;
        AA[i_JAA] = value;
        if (i < old_i)
        {
            return NO_SORT;
        }
        else
        {
            JA[i_JAA] = j - 1;
            if (i == old_i)
            {
                if (j <= old_j)
                    return NO_SORT;
            }
            else
            {
                IA[i - 1] = i_JAA;
            }
        }
        old_i = i;
        old_j = j;
        i_JAA++;
        getline (file, line);
        str_index = 0;
    }
    IA[height] = i_JAA;

    // Fichier-matrice contenait des valeurs nulles => on redimensionne AA & JA
    if (i_JAA < JAA_size)
    {
        double *AA_tmp = new double[i_JAA];
        unsigned int *JA_tmp = new unsigned int[i_JAA];
        for (unsigned int i = 0; i < i_JAA; i++)
        {
            AA_tmp[i] = AA[i];
            JA_tmp[i] = JA[i];
        }
        delete[] AA;
        AA = AA_tmp;
        delete[] JA;
        JA = JA_tmp;
        JAA_size = i_JAA;
    }

    return NO;
}


bool CSR::read_separator (unsigned int &index, std::string line)
{
    if (line[index] != ' ' && line[index] != '\t' && line[index] != '\n')
        return false;
    index++;
    while (line[index] == ' ' || line[index] == '\t' || line[index] == '\n')
        index++;
    return true;
}


bool CSR::read_uint (unsigned int &index, std::string line, unsigned int &res)
{
    char read = line[index];
    if (read < '0' || read > '9')
        return false;
    res = read - '0';
    index++;
    read = line[index];
    while (read >= '0' && read <= '9')
    {
        res *= 10;
        res += read - '0';
        index++;
        read = line[index];
    }
    return true;
}


bool CSR::read_d (unsigned int &index, std::string line, double &res)
{
    char read = line[index];
    if (read != '-' && (read < '0' || read > '9') )
        return false;

    std::string nbr;
    while ( (read >= '0' && read <= '9') || read == '-' || read == '+'
            || read == '.' || read == 'e')
    {
        nbr += read;
        index++;
        read = line[index];
    }

    res = atof (nbr.c_str() );
    return true;
}


CSR::CSR (unsigned int w, unsigned int h, unsigned int jsize, double *aa,
          unsigned int *ja, unsigned int *ia) :
    width (w), height (h), JAA_size (jsize), AA (aa), JA (ja), IA (ia)
{
}


CSR::CSR (MatLC *matLC)
{
    matLC->calcule_CSR (&AA, &JA, &IA, &width, &height, &JAA_size);
}


CSR& CSR::operator= (const CSR &c)
{
    if (this != &c)
    {
        // 1-Copie
        double* AA_tmp = new double[c.JAA_size];
        for (unsigned int i = 0; i < c.JAA_size; i++)
            AA_tmp[i] = c.AA[i];
        unsigned int* JA_tmp = new unsigned int[c.JAA_size];
        for (unsigned int i = 0; i < c.JAA_size; i++)
            JA_tmp[i] = c.JA[i];
        unsigned int* IA_tmp = new unsigned int[c.height + 1];
        for (unsigned int i = 0; i <= c.height; i++)
            IA_tmp[i] = c.IA[i];

        // 2-Destruction
        byebye();

        // 3-Réassignement
        JAA_size = c.JAA_size;
        height = c.height;
        width = c.width;
        AA = AA_tmp;
        JA = JA_tmp;
        IA = IA_tmp;
    }

    return *this;
}


double CSR::get_coeff (unsigned int i, unsigned int j) const
{
    if (! (i < height && j < width) )
    {
        TRACE_ ("CSR::get_coeff - indices trop grands")
        return 0.0;
    }
    for (unsigned int p = IA[i]; p < IA[i + 1]; p++)
    {
        if (JA[p] == j)
            return AA[p];
    }
    return 0.0;
}


void CSR::display_csr() const
{
    std::cout << "M: " << std::endl;
    std::cout << "~AA: ";
    for (unsigned int i = 0; i < JAA_size; i++)
        std::cout << ' ' << AA[i];
    std::cout << std::endl;
    std::cout << "~JA: ";
    for (unsigned int i = 0; i < JAA_size; i ++)
        std::cout << ' ' << JA[i];
    std::cout << std::endl;
    std::cout << "~IA: ";
    for (unsigned int i = 0; i <= height; i ++)
        std::cout << ' ' << IA[i];
    std::cout << std::endl;
}


void CSR::display_full() const
{
    unsigned int	i_JAA = 0;

    std::cout << "M: " << std::endl;
    for (unsigned int j = 0; j < height; j++)
    {
        for (unsigned int i = 0; i < width; i++)
        {
            if ( (i_JAA < IA[j + 1]) && (JA[i_JAA] == i) )
            {
                std::cout << ' ' << AA[i_JAA];
                i_JAA++;
            }
            else
            {
                std::cout << " 0";
            }
        }
        std::cout << std::endl;
    }
}


CSR CSR::operator* (const double d) const
{
    CSR res (*this);

    for (unsigned int j = 0; j < JAA_size; j++)
        res.AA[j] *= d;

    return res;
}


CSR CSR::operator* (const CSR &mat) const
{
    MatLC *A = this->conversion_MatLC();
    MatLC *B = mat.conversion_MatLC();
    MatLC *C = A->produit (B);
    delete A;
    delete B;
    CSR res (C);
    delete C;
    return res;
}


Vector CSR::operator* (const Vector& v) const
{
    Vector res (height);

    if (v.size() != width)
        return res;

    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = IA[i]; j < IA[i + 1]; j++)
            res[i] += AA[j] * v.get ( (int) JA[j]);
    }

    return res;
}


Vector CSR::mult_add (Vector x, Vector b) const
{
    Vector res (height);

    if (x.size() != width || b.size() != width)
        return res;

    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = IA[i]; j < IA[i + 1]; j++)
            res[i] += AA[j] * x[JA[j]];
        res[i] += b[i];
    }
    return res;
}


// Comportement non testé sur matrices non carrées
double CSR::puiss_iter (double epsilon) const
{
    if (epsilon <= 0)
        return 0;

    // Initialisation
    Vector	v (width),
            v_norm (width);
    for (unsigned int i = 0; i < v.size(); i ++)
        v[i] = 1;
    double	anci_lambda,
            lambda = 0;

    // Boucle principale
    do
    {
        anci_lambda = lambda;
        v_norm = v / v.norm();
        v = (*this) * v_norm;
        lambda = v * v_norm;
        TRACE_ ("lambda : " << lambda)
    }
    while (fabs (lambda - anci_lambda) > epsilon);

    return lambda;
}


// Semble ne pas fonctionner sur non carrées
CSR CSR::transpose() const
{
    CSR t;
    t.AA = new double[JAA_size];
    t.JA = new unsigned int[JAA_size];
    t.IA = new unsigned int[width + 1];
    t.JAA_size = JAA_size;
    t.height = width;
    t.width = height;

    // Construction de t.IA
    for (unsigned int i = 0; i < width; i++)
        t.IA[i] = 0;
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = IA[i]; j < IA[i + 1]; j++)
        {
            t.IA[JA[j] + 1]++;
        }
    }
    for (unsigned int i = 0; i < width; i++)
        t.IA[i + 1] += t.IA[i];
    t.IA[width] = JAA_size;

    // Construction de t.AA
    int *temp = new int[width];
    for (unsigned int i = 0; i < width; i++)
        temp[i] = 0;
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = IA[i]; j < IA[i + 1]; j++)
        {
            t.AA[t.IA[JA[j]] + temp[JA[j]]] = AA[j];
            t.JA[t.IA[JA[j]] + temp[JA[j]]] = i;
            temp[JA[j]]++;
        }
    }
    delete[] temp;

    return t;
}


CSR CSR::operator+ (const CSR &m) const
{
    if (width != m.width || height != m.height)
    {
        TRACE_ ("Addition de matrices: tailles incompatibles")
        return CSR();
    }

    // Initialisation
    CSR res;
    res.height = height;
    res.width = width;
    res.IA = new unsigned int[width + 1];
    for (unsigned int i = 0; i < width; i++)
        res.IA[i] = 0;

    unsigned int nbr_elem = 0;
    // La taille de la somme n'est pas connue d'avance, on redimensionnera apres :
    double *resAA = new double[JAA_size + m.JAA_size];
    unsigned int *resJA = new unsigned int[JAA_size + m.JAA_size];

    // Calcul de la somme
    for (unsigned int i = 0; i < width; i++)   //i ~ ligne actuelle
    {
        unsigned int j1 = IA[i], j2 = m.IA[i]; // j ~ nombres d'elements de la matrice passes
        bool end_of_line_1 = false, end_of_line_2 = false;
        while (! (end_of_line_1 && end_of_line_2) )
        {
            if (!end_of_line_2 && (end_of_line_1 || (JA[j1] > m.JA[j2]) ) ) // element de m à ajouter
            {
                resAA[nbr_elem] = m.AA[j2];
                resJA[nbr_elem] = m.JA[j2];
                j2++;
                if (j2 >= m.IA[i + 1])
                    end_of_line_2 = true;
            }
            else if (!end_of_line_1 && (end_of_line_2 || (m.JA[j2] > JA[j1]) ) )   // element de *this à ajouter
            {
                resAA[nbr_elem] = AA[j1];
                resJA[nbr_elem] = JA[j1];
                j1++;
                if (j1 >= IA[i + 1])
                    end_of_line_1 = true;
            }
            else  	// somme des elements de *this et m à ajouter
            {
                if (AA[j1] + m.AA[j2] == 0)   // si les elements se neutralisent
                {
                    nbr_elem--;
                    res.IA[i]--;
                }
                else
                {
                    resAA[nbr_elem] = AA[j1] + m.AA[j2];
                    resJA[nbr_elem] = JA[j1];
                }
                j1++;
                j2++;
                if (j2 >= m.IA[i + 1])
                    end_of_line_2 = true;
                if (j1 >= IA[i + 1])
                    end_of_line_1 = true;
            }
            nbr_elem++;
            res.IA[i + 1]++;
        }
        res.IA[i + 1] += res.IA[i];
    }

    // Redimensionnement et copie des vecteurs
    res.IA[height] = nbr_elem + 1;

    res.JAA_size = nbr_elem;
    res.AA = new double[res.JAA_size];
    res.JA = new unsigned int[res.JAA_size];
    for (unsigned int j = 0; j < nbr_elem; j++)
    {
        res.AA[j] = resAA[j];
        res.JA[j] = resJA[j];
    }

    delete[] resAA;
    delete[] resJA;

    return res;
}


Vector CSR::resoudre_systeme_lineaire (Vector b, double epsilon, unsigned int max_iter) const
{
    if (width != height)
    {
        TRACE_ ("CSR::resoudre_systeme_lineaire - Matrice non carrée");
    }

    CSR adjoint (*this);
    double alpha = 0, beta = 0;
    Vector	rprec, sprec,
            x (b), y (b),
            r (mult_add (-x, b) ),
            s (adjoint.mult_add (-y, b) ),
            d (r), f (s);

    unsigned int compteur = 0;
    while ( (mult_add (x, -b).norm() > epsilon) && (compteur < max_iter) )
    {
        alpha = (s * r) / (f * ( (*this) * d) );
        y += f * alpha;
        x += d * alpha;
        rprec = r;
        r += ( ( (*this) * d) * (- alpha) );
        sprec = s;
        s -= ( (adjoint * f) * alpha);
        beta = (s * r) / (sprec * rprec);
        d *= beta;
        d += r;
        f *= beta;
        f += s;
        compteur++;
    }

    if (compteur == max_iter)
    {
        TRACE_ ("CSR::resoudre_systeme_lineaire - Divergence possible");
    }

    return x;
}


bool CSR::iteration_de_rayleigh (double &lambda, Vector &v, double epsilon, unsigned int max_iter) const
{
    if (width != height)
    {
        TRACE_ ("CSR::iteration_de_rayleigh - Matrice non carrée");
    }

    v *= (1 / v.norm() );
    lambda = v * ( (*this) * v);
    Vector vprec (v * 2);
    CSR blop, id (width);

    unsigned int compteur = 0;
    while ( ( (vprec - v).norm() > epsilon) && (compteur < max_iter) )
    {
        vprec = v;
        blop = id * (-lambda);
        blop += (*this);
        v = blop.resoudre_systeme_lineaire (v, epsilon, 500);
        v *= (1 / v.norm() );
        lambda = v * ( (*this) * v);
        compteur++;
    }

    if (compteur == max_iter)
    {
        TRACE_ ("CSR::iteration_de_rayleigh - Divergence possible");
        return false;
    }

    return true;
}


CSR CSR::decompoQR()
{
    MatLC *q = new MatLC (AA, JA, IA, width, height);
    MatLC *r = q->decompoQR();
    changerEn (r);
    return CSR (q);
}


void CSR::changerEn (MatLC *matlc)
{
    byebye();
    matlc->calcule_CSR (&AA, &JA, &IA, &width, &height, &JAA_size);
}


MatLC *CSR::conversion_MatLC() const
{
    return new MatLC (AA, JA, IA, width, height);
}


void CSR::supprEmptyLines()
{
    unsigned int *IA_tmp = new unsigned int[height + 1];
    unsigned int deleted_lines = 0;

    IA_tmp[0] = 0;
    for (unsigned int i_col = 1; i_col <= height; i_col++)
    {
        if (!IA[i_col])
            deleted_lines++;
        else
            IA_tmp[i_col - deleted_lines] = IA[i_col];
    }

    height -= deleted_lines;
    delete IA;
    IA = new unsigned int[height + 1];
    for (unsigned int i_col = 0; i_col <= height; i_col++)
        IA[i_col] = IA_tmp[i_col];

    delete IA_tmp;
}


void CSR::stochastiser()
{
    double *column_sum = new double[width];

    for (unsigned int i_col = 0; i_col < width; i_col++)
        column_sum[i_col] = 0.f;

    unsigned int i_col, i_row = 0;
    for (unsigned int i_JAA = 0; i_JAA < JAA_size; i_JAA++)
    {
        if (i_JAA >= IA[i_row + 1])
            i_row++;
        i_col = JA[i_JAA];
        if (i_row == i_col)
            AA[i_JAA] = 0.f;
        else
            column_sum[i_col] += AA[i_JAA];
    }

    for (unsigned int i_JAA = 0; i_JAA < JAA_size; i_JAA++)
        AA[i_JAA] /= column_sum[JA[i_JAA]];

    delete column_sum;
}


Vector CSR::googleEigenVector (double m, double epsilon) const
{
    if (height != width)
    {
        Vector v;
        v[0] = -1;
        return v;
    }

    Vector s (height);
    for (unsigned int i = 0; i < height; i++)
        s[i] = 1.f / height;

    Vector old_x, x = s;

    do
    {
        old_x = x;
        x = mult_add (x * (1 - m), s * m);
    }
    while ( (x - old_x).norm() > epsilon);

    double sum = 0;
    for (unsigned int i = 0; i < x.size(); i++)
        sum += x[i];

    return x;
}
