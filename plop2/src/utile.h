/**
 * @file utile.h
 * @brief Macro utile
 *
 * @author CIMON Lucas
 * @date été 2010
 */
#ifndef _DEF_H_UTILE
#define _DEF_H_UTILE


/**
 * @def TRACE
 * @brief Macro de suivi de l'éxécution
 Définit les macros TRACE & TRACE_ (erreurs) de niveau 1
 et TRACE2 de niveau 2.
 Attention: si ce module est supprimé, toutes les macro de TRACE doivent le
 suivre dans la tombe ou être définies ailleurs.
 Couleur "\033[3"_c_"m" :
	_c_ = 0 => noir
	_c_ = 1 => rouge
	_c_ = 2 => vert
	_c_ = 3 => jaune
	_c_ = 4 => bleu foncé
	_c_ = 5 => violet
	_c_ = 6 => bleu clair
	_c_ = 7 => gris
 */
#ifndef TRACE_DISPLAY
#define TRACE_DISPLAY 1
#endif

#if TRACE_DISPLAY==1
#define TRACE(string)	std::cerr << "\033[32m" << string << "\033[0m" << std::endl;
#define TRACE_(string)	std::cerr << "\033[31m" << string << "\033[0m" << std::endl;
#define TRACE2(string)
#elif TRACE_DISPLAY==2
#define TRACE(string)	std::cerr << "\033[32m" << string << "\033[0m" << std::endl;
#define TRACE_(string)	std::cerr << "\033[31m" << string << "\033[0m" << std::endl;
#define TRACE2(string)	std::cerr << "\033[33m" << string << "\033[0m" << std::endl;
#else
#define TRACE(string)
#define TRACE2(string)
#endif

#include <iostream>

#endif
