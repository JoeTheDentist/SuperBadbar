#include "matLC.h"

#include <iostream>
#include <math.h>
#include "utile.h"

const double MatLC::rapport_coeff_precision = 100.0;


MatLC::MatLC(unsigned int n) 
{
	width = n;
	height = n;	
	maillon m;
	m.val = 1;
	ligne = new std::list<struct maillon>[height];
	for (unsigned i = 0; i < height; i++) {
		m.col = i;
		ligne[i].push_back(m);
	}
	epsilon = 1.f / rapport_coeff_precision;
}


MatLC::MatLC(unsigned int i, unsigned int j)
{
	width = j;
	height = i;	
 	ligne = new std::list<struct maillon>[height];
	epsilon = 1.f / rapport_coeff_precision;
}


MatLC::MatLC(double *AA, unsigned int *JA, unsigned int *IA, unsigned int w, unsigned int h) 
{
	width = w;
	height = h;
	maillon m;
	epsilon = 1/rapport_coeff_precision;
	ligne = new std::list<struct maillon>[height];
	for (unsigned i = 0; i < height; i++) {
		for (unsigned int k = IA[i]; k < IA[i+1]; k++) {
			m.val = AA[k];
			m.col = JA[k];
			ligne[i].push_back(m);
			if ((m.val!=0) && (fabs(m.val)/rapport_coeff_precision < epsilon))
				epsilon = fabs(m.val);
		}
	}
}


MatLC::MatLC(const MatLC& mat) : width(mat.width), height(mat.height)
{  
	ligne = new std::list<struct maillon>[height];
	for (unsigned int i = 0; i < height; i++) {
		ligne[i] = mat.ligne[i];
	}
	epsilon = mat.epsilon;
}


MatLC::~MatLC() 
{
	delete[] ligne; // c'est magique le delete
	ligne = NULL;
}


MatLC& MatLC::operator=(const MatLC &mat)
{
	if (ligne!=NULL)
		delete[] ligne;
	ligne = new std::list<struct maillon>[height];
	width = mat.width;
	height = mat.height;
	for (unsigned int i = 0; i < height; i++) {
		ligne[i] = mat.ligne[i];
	}
	epsilon = mat.epsilon;
	return *this;
}


void MatLC::calcule_CSR(double **aa, unsigned int **ja, unsigned int **ia, unsigned int *w, unsigned int *h, unsigned int *j_size)
{
	double *AA;
	unsigned int *JA, *IA;
	std::list<struct maillon>::iterator curs;
	unsigned jsize = 0;
	for (unsigned int i = 0; i < height; i++) {
		jsize += ligne[i].size();
	}
	AA = new double[jsize];
	JA = new unsigned int[jsize];
	IA = new unsigned int[width + 1];
	unsigned int k = 0;
	for (unsigned int i = 0; i < height; i++) {
		IA[i] = k;
		for(curs = ligne[i].begin(); curs != ligne[i].end(); curs++) {
			k++;
		}
	}
	IA[height] = jsize;
	k = 0;
	for (unsigned int i = 0; i < height; i++) {
		for(curs = ligne[i].begin(); curs != ligne[i].end(); curs++) {
			JA[k] = curs->col;
			AA[k] = curs->val;
			k++;
		}
	}	
	*w = width;
	*h = height;
	*j_size = jsize;
	*aa = AA;
	*ia = IA;
	*ja = JA;
}


double MatLC::get_coeff(unsigned int lig, unsigned int col) 
{
	if ((int)lig < 0 || lig >= height || (int)col < 0 || col >= width) {
		TRACE("Attention: coefficients incorrects dans get_coeff de MatLC");
		return 0.0;
	}
	std::list<struct maillon>::iterator curs; 
	for (curs = ligne[lig].begin(); curs->col < col; curs++) {;}
	if (curs->col == col)
		return curs->val;
	else
		return 0.0;
}


void MatLC::set_coeff(unsigned int lig, unsigned int col, double x)
{
	if (x!=0 && fabs(x)/rapport_coeff_precision < epsilon)
		epsilon = fabs(x)/rapport_coeff_precision;	
	set_coeff_intern(lig, col, x);
}


void MatLC::set_coeff_intern(unsigned int lig, unsigned int col, double x)
{
	std::list<struct maillon>::iterator curs; 
	maillon m;
	m.val = x;
	m.col = col;
	if ((int)lig < 0 || lig >= height || (int)col < 0 || col >= width) {
		TRACE("Attention: coefficients incorrects dans set_coeff de MatLC");
		return ;
	}
	for (curs = ligne[lig].begin(); curs->col < col && curs!=ligne[lig].end(); curs++) {;}
	if (curs->col == col) {
		if (presque_nul(x))
			ligne[lig].erase(curs);
		else
			curs->val = x;
	}
	else {
		if (!presque_nul(x))
			ligne[lig].insert(curs, m);
	}
}


bool MatLC::presque_nul(double d) 
{
//~ 	TRACE(epsilon);
	return fabs(d) <= epsilon;
}


void MatLC::incr_coeff_intern(unsigned int lig, unsigned int col, double x)
{
	if(presque_nul(x))
		return;
	std::list<struct maillon>::iterator curs; 
	maillon m;
	m.col = col;
	m.val = x;
	if ((int)lig < 0 || lig >= height || (int)col < 0 || col >= width) {
		TRACE("Attention: coefficients incorrects dans incr_coeff de MatLC");
		return ;
	}
	for (curs = ligne[lig].begin(); curs->col < col && curs!=ligne[lig].end(); curs++) {;}
	if (curs == ligne[lig].end()) {
		if(!presque_nul(x))
			ligne[lig].push_back(m);
		return;
	}
	if (curs->col == col) {
		if (!presque_nul(curs->val + x)) {                                           
			curs->val += x;
		} else {
			ligne[lig].erase(curs);
		}
	} else {
			ligne[lig].insert(curs, m);
	}
}


void MatLC::incr_coeff(unsigned int lig, unsigned int col, double x)
{
	if (x!=0 && fabs(x)/rapport_coeff_precision < epsilon)
		epsilon = fabs(x)/rapport_coeff_precision;
	incr_coeff_intern(lig,col,x);
}


void MatLC::display()
{
	for (unsigned int i = 0;  i < height; i++) {
		std::list<struct maillon>::iterator curs = ligne[i].begin();
		for (unsigned int j = 0; j < width; j++) {
			if ((curs!=ligne[i].end()) && (j == curs->col)) {
				std::cout << " " << curs->val;
				curs++;
			}
			else {
				std::cout << " 0";
			}
		}
		std::cout << std::endl;
	}
}


MatLC *MatLC::transpose()
{
	MatLC *t = new MatLC(width);
	std::list<struct maillon>::iterator curs;
	for (unsigned int i = 0; i < height; i++)
		t->set_coeff_intern(i,i,0);
	for (unsigned int i = 0; i < height; i++) {
		for (curs = ligne[i].begin(); curs != ligne[i].end(); curs++) {
			maillon m;
			m.val = curs->val;
			m.col = i;
			t->ligne[curs->col].push_back(m);
		}
	}
	return t;
}


MatLC *MatLC::produit(MatLC *B) 
{
	MatLC *tA = this->transpose(); // pour les notations.. on fait C = A*B
	MatLC *C = new MatLC(height, width); 
	std::list<struct maillon>::iterator cursA, cursB;
	for (unsigned int i = 0; i < height; i++) {
		for (cursB = B->ligne[i].begin(); cursB != B->ligne[i].end(); cursB++) {
			for (cursA = tA->ligne[i].begin(); cursA != tA->ligne[i].end(); cursA++) {
				C->incr_coeff_intern(cursB->col, cursA->col, cursB->val * cursA->val);
			}
		}
	}
	MatLC *res = C->transpose();
	delete tA;
	delete C;
	return res;
}


double MatLC::trace()
{
	int tr = 0;
	for (unsigned int i = 0; i < width; i++) {
		tr += get_coeff(i,i);
	}
	return tr;
}


MatLC *MatLC::decompoQR()
{
	MatLC *H = new MatLC(width);
	std::list<struct maillon>::iterator curs;
	double *v = new double[width];
	double alpha, beta;
	for (unsigned int k = 0; k < width-1; k++) {
		alpha = 0;
		for (curs = ligne[k].begin(); curs!=ligne[k].end(); curs++) {
			if (curs->col >= k)
				alpha += pow(curs->val, 2);
		}
		alpha = sqrt(alpha);
		
		v[k] = get_coeff(k,k) - alpha;
		beta = alpha * (alpha - get_coeff(k,k));
			
		for (unsigned i = k+1; i < width; i++) 
			v[i] = 0;
		for (curs = ligne[k].begin(); curs!=ligne[k].end(); curs++) {
			if (curs->col > k)
				v[curs->col] = curs->val;
		}		
		for (unsigned int j = k; j < height; j++) {
			double c = 0;
			for (curs = ligne[j].begin(); curs!=ligne[j].end(); curs++) {
				if (curs->col >= k)
					c += v[curs->col] * curs->val;
			}
			if (beta == 0) 
				c = 1;
			else 
				c /= beta;
			for (unsigned int i = k; i < width; i++) {
				incr_coeff_intern(j,i, (- c) * v[i]);
			}
		}
		
		for (unsigned int j = 0; j < width; j++) {
			double c = 0;
			for (curs = H->ligne[j].begin(); curs!=H->ligne[j].end(); curs++) {
				if (curs->col >= k)
					c += v[curs->col] * curs->val;
			}
			if (beta == 0) 
				c = 1;
			else 
				c /= beta;
			for (unsigned int i = k; i < width; i++) {
				H->incr_coeff_intern(j, i, (- c) * v[i]);
			}
		}
	}
	MatLC *res = H->transpose();
	delete[] v;
	delete H;
	return res;
}

