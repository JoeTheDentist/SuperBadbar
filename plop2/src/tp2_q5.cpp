#include "vector.h"
#include "csr.h"

#include "utile.h" // Contient la macro TRACE

#include <cstdlib>


bool loadMat(CSR& mat, const char* file, const char* name)
{
	if (!mat.load(file)) {
		TRACE("\tLe fichier " << file
			<< " ne peut être ouvert. Test annulé.")
		return false;
	}
	if (name) {
		TRACE(name)
		mat.display_full();
	}
		
	return true;
}


int main()
{
	CSR A;
	if(!loadMat(A, "../mat/q5_test.mtx", "MATRICE DU RESEAU SANS NOEUD PENDANT:"))
		return 1;
	
	A.stochastiser();
	TRACE("\nVecteur propre q recherché :")
	A.googleEigenVector(0.15, 0.00001).display();

	
	TRACE("\n/**************/\n")

	
	if(!loadMat(A, "../mat/q5_imag50.mtx", "MATRICE DU RESEAU SANS NOEUD PENDANT:"))
		return 1;

	A.stochastiser();
	TRACE("\nVecteur propre q recherché :")
	A.googleEigenVector(0.15, 0.001).display();

	
	return 0;
}
