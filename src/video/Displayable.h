/**
 * 	@file displayable.h
 * 	@brief header de la classe Displayable
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _DISPLAYABLE_
#define _DISPLAYABLE_

#include "../util/debug.h"

class Surface;
struct Rect;

class Displayable {
protected:
public:
	virtual Surface *current_picture() const = 0;
	virtual Rect position() const = 0;
};

#endif

