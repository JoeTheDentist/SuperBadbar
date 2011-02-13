#include <iostream>

#include "displayable.h"


/*Surface * Displayable::current_picture() {
    PRINT_CONSTR(1, "current_picture de Displayable")
    return NULL;
}

Rect Displayable::position() {
    Rect r;
    return r;
}*/

int Displayable::get_level() {
    return m_level;
}

void Displayable::set_level(int level) {
    m_level = level;
}
