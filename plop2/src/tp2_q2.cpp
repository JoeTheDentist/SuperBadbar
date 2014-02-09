#include "vector.h"
#include "csr.h"

#include "utile.h" // Contient la macro TRACE


bool loadMat (CSR& mat, const char* file, const char* name)
{
    if (!mat.load (file) )
    {
        TRACE ("\tLe fichier " << file
               << " ne peut être ouvert. Test annulé.")
        return false;
    }
    if (name)
    {
        TRACE (name)
        mat.display_full();
    }

    return true;
}


bool getBiggestEigenValue (CSR& mat, double epsilon)
{
    unsigned int width = mat.get_width(), height = mat.get_height();
    TRACE ("\n\tTaille : " << width << " x " << height << ", "
           << mat.get_nnz() << " nnz")
    if (width != height)
        return false;

    double lambda = mat.puiss_iter (epsilon);
    TRACE ("\n\tprod.puiss_iter(" << epsilon << ") : " << lambda);

    return true;
}


int main()
{
    CSR diag;
    if (!loadMat (diag, "../mat/q2_diag.mtx", "MATRICE DIAGONALE:") )
        return 1;

    CSR test;
    if (!loadMat (test, "../mat/q2_test.mtx", "MATRICE DE TEST:") )
        return 1;

    CSR test_inv;
    if (!loadMat (test_inv, "../mat/q2_test_inv.mtx",
                  "INVERSE DE LA MATRICE DE TEST:") )
        return 1;


    CSR prod = test_inv * (diag * test);
    TRACE ("\nPRODUIT:")
    prod.display_full();


    if (!getBiggestEigenValue (prod, 0.0001) )
        return 1;


    TRACE ("\n/**************/\n")

    /*
    CSR s3dkt3m2;
    if (!loadMat(s3dkt3m2, "../s3dkt3m2.mtx", NULL))
    	return 1;

    TRACE("s3dkt3m2:")
    if (!getBiggestEigenValue(s3dkt3m2, 0.0001))
    	return 1;
    */
    /*
    CSR s1rmq4m1;
    if (!loadMat(s1rmq4m1, "../s1rmq4m1.mtx", NULL))
    	return 1;

    TRACE("s1rmq4m1:")
    if (!getBiggestEigenValue(s1rmq4m1, 0.0001))
    	return 1;
    */

    return 0;
}
