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
	CSR M;
	if(!loadMat(M, "../mat/q2_diag.mtx", "MATRICE DU SYSTEME LINEAIRE:"))
		return 1;
	
	Vector b(M.get_width());
	for (int i = 0; i < b.size(); i++)
		b[i] = 1;
	TRACE("\nb =")
	b.display();
	
	Vector x = M.resoudre_systeme_lineaire(b, 0.0001, 500);
	TRACE("\nSolution de (M.x = b) :")
	x.display();

	TRACE("\nVérification : M.x =")
	(M * x).display();
	
	
	TRACE("\n/**************/\n")


	double lambda = 0 ;
	Vector v(M.get_width(), true); // Vecteur aléatoire positif
	
	M.iteration_de_rayleigh(lambda, v, 0.0001);
	TRACE("\nValeur propre = " << lambda)
	
	TRACE("\nVecteur propre =")
	v.display();
	
	TRACE("\nM * vecteur propre / valeur propre =")
	((M * v) * (1 / lambda)).display();
	
	
	return 0;
}
