/**
 * 	@file rect.cpp
 * 	@brief Implémentation de la classe Rect
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 */

#include "Rect.h"


Rect::Rect(int x_, int y_, int w_, int h_ ):
	x(x_),
	y(y_),
	w(w_),
	h(h_)
{
	
}

Rect::Rect(Rect const &rect):
	x(rect.x),
	y(rect.y),
	w(rect.w),
	h(rect.h)
{
	
}

Rect::~Rect()
{
	
}

int Rect::norm_2() const
{
	return (*this) * (*this);
}

int Rect::det(const Rect rect) const
{
	return x * rect.y - rect.x * y;
}

Rect Rect::operator+ (const Rect &rect2) const
{
	Rect res = (*this);
	res.x += rect2.x;
	res.y += rect2.y;
	return res;
}

Rect Rect::operator- (const Rect &rect2) const
{
	Rect res = (*this);
	res.x -= rect2.x;
	res.y -= rect2.y;
	return res;
}

int Rect::operator* (const Rect &rect2) const
{
	return x * rect2.x + y * rect2.y;
}
