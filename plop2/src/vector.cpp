#include "vector.h"

#include "utile.h"

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <limits>


Vector::Vector() : n(0), val(NULL) {}

	
Vector::Vector(unsigned int size) : n(size)
{
	val = (double *)malloc(n * sizeof(double));
	for (unsigned int i = 0; i < n; i++)
		val[i] = 0;
}


Vector::Vector(unsigned int size, bool only_positive) : n(size)
{
    srand((unsigned)(time(0)));
	val = (double *)malloc(n * sizeof(double));
	if (only_positive) {
		for (unsigned int i = 0; i < n; i++)
			val[i] = rand()/(double(RAND_MAX)+1);
	} else {
		for (unsigned int i = 0; i < n; i++)
			val[i] = (rand() - RAND_MAX / 2)/((double(RAND_MAX) + 1) / 2);		
	}
}


Vector::Vector(const Vector& v) : n(v.n)
{
	val = (double *)malloc(n * sizeof(double));
	for (unsigned int i = 0; i < n; i++)
		val[i] = v.val[i];
}


Vector::~Vector()
{
	if (val)
		free(val);
}


void Vector::display() const
{
	std::cout << "V:";
	for (unsigned int i = 0; i < n; i++) {
		std::cout << ' ';
		std::cout << val[i];
	}
	std::cout << std::endl;
}


unsigned int Vector::size() const
{
	return n;
}


double Vector::norm() const
{
	double carre = 0;
	for (unsigned int i = 0; i < n; i++)
		carre += val[i] * val[i];
	
	return sqrt(carre);
	
}


void Vector::resize(unsigned int size)
{
	if (n == size)
		return;
	
	val = (double *)realloc(val, size * sizeof(double));
	
	if (size > n)
		for (unsigned int i = n; i < size; i++)
			val[i] = 0.f;
	
	n = size;
}


double& Vector::operator[](int i)
{
	if (!n || i >= (int)n)
		resize(i + 1);
	
	if (i < 0) {
		i *= -1;
		i = (i > (int)n) ? 1 : i;
		return val[n - (unsigned int)i];
	} else {
		return val[i];
	}
}


double Vector::get(int i) const
{
	if (!n || i >= (int)n)
		return std::numeric_limits<double>::infinity();
	
	if (i < 0) {
		i *= -1;
		i = (i > (int)n) ? 1 : i;
		return val[n - (unsigned int)i];
	} else {
		return val[i];
	}
}


void Vector::operator=(const Vector &v)
{
	if (v.n != n) {
		val = (double *)realloc(val, v.n * sizeof(double));
		n = v.n;
	}
	for (unsigned int i = 0; i < n; i++)
		val[i] = v.val[i];
}


Vector Vector::operator+(const Vector &v) const
{
	if (n != v.n) {
		TRACE_("Tailles incompatibles pour une addition")
		return Vector();
	}
	Vector res(n);
	for (unsigned int i = 0; i < n; i++)
		res[i] = val[i] + v.val[i];
	return res;
}


Vector Vector::operator-(const Vector &v) const
{
	if (n != v.n) {
		TRACE_("Tailles incompatibles pour une soustraction")
		return Vector();
	}
	Vector res(n);
	for (unsigned int i = 0; i < n; i++)
		res[i] = val[i] - v.val[i];
	return res;
}


double Vector::operator*(const Vector &v) const
{
	if (n != v.n)
		return 0;
	double res = 0;
	for (unsigned int i = 0; i < n; i++)
		res += val[i] * v.val[i];
	return res;
}


Vector Vector::fwd_prod(const Vector &v)
{
	if (n != v.n) {
		TRACE_("Tailles incompatibles pour un produit")
		return Vector();
	}
	Vector res(n);
	for (unsigned int i = 0; i < n; i++)
		res[i] = val[i] * v.val[i];
	return res;
}


Vector Vector::operator*(const double d) const
{	
	Vector res(n);
	for (unsigned int i = 0; i < n; i++)
		res[i] = val[i] * d;
	return res;
}


Vector Vector::operator/(const double d) const
{	
	if (d == 0) {
		TRACE_("Impossible de diviser par 0!")
		return Vector();
	}
	return (*this) * (1/d);
}


Vector Vector::operator-() const
{
	Vector res(n);
	for (unsigned int i = 0; i < n; i++)
		res[i] = - val[i];
	return res;
}


Vector Vector::operator+=(const Vector &v)
{
	if (n != v.n) {
		TRACE_("Tailles incompatibles pour une addition")
		return Vector();
	}
	for (unsigned int i = 0; i < n; i++)
		val[i] += v.val[i];
	return Vector(*this);
}


Vector Vector::operator-=(const Vector &v)
{
	if (n != v.n) {
		TRACE_("Tailles incompatibles pour une addition")
		return Vector();
	}
	for (unsigned int i = 0; i < n; i++)
		val[i] -= v.val[i];
	return Vector(*this);
}


Vector Vector::operator*=(const double d)
{
	for (unsigned int i = 0; i < n; i++)
		val[i] *= d;
	return Vector(*this);
}
