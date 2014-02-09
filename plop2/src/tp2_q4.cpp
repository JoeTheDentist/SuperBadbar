#include "vector.h"
#include "csr.h"

#include "utile.h" // Contient la macro TRACE

#include <cstdlib>


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


int main()
{
    CSR R;
    if (!loadMat (R, "../mat/q4_test.mtx", "MATRICE DECOMPOSEE:") )
        return 1;


    CSR Q = R.decompoQR();
    TRACE ("\nQ =");
    Q.display_full();
    TRACE ("\nR =");
    R.display_full();

    TRACE ("\nPRODUIT Q*R =");
    (Q * R).display_full();


    return 0;
}
