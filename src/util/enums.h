/**
 * 	@file enums.h
 * 	@brief Contient la definition des enumerations du jeu
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 */


#ifndef _BABAR_ENUM_H
#define _BABAR_ENUM_H


enum key
{
    k_none = 0, k_exit, k_escape, k_up, k_down, k_right, k_left, k_next_weapon, k_prev_weapon, k_action, k_jump, k_fire //k_fire doit etre le dernier
};

enum menu_key
{
    mk_up, mk_down, mk_left, mk_right, mk_enter, mk_exit, mk_escape, mk_none
};




#endif
