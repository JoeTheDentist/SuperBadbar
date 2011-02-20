/** * 	@file displayable.h * 	@brief header de la classe Displayable * * 	@author Guillaume Bérard & Benoit Morel * 	@date decembre 2010 * */#ifndef _DISPLAYABLE_#define _DISPLAYABLE_#include "../util/globals.h"
#include "../util/debug.h"
class Surface;class Displayable {protected:	int m_level; /* niveau dans l'ordre d'affichage, plus c'est grand, plus il sera devant */public:	virtual Surface *current_picture() const = 0;	virtual Rect position() const = 0;
	int get_level();
	void set_level(int level);};#endif
