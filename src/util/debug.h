/**
 * 	@file debug.h
 * 	@brief Macros de debug / traces pour le développement
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 * Trois macros de debug et une de performance:
 * PRINT_CONSTR pour tracer les constructeurs et destructeurs,
 * PRINT_TRACE pour tracer le reste
 * PRINT_DEBUG  pour du debugage localisé et pour les messages d'erreurs classiques
 * Chacune utilise une constante définie dans ce fichier afin de déterminer la
 * précision des messages: 0 pour n'afficher aucun message, 3 pour afficher le maximum
 * de messages.
 * Ces messages ne doivent pas apparaitre dans le projet final et servent seulement �  suivre
 * le comportement du programme.
 *
 *
 * PRINT_PERF():  macro utilisée par Game pour afficher
 * le pourcentage de cpu utilisé par le programme sur un tour
 * de jeu
 * La constante PERF_CYCLES correspond au nombre de cycles
 * entre lesquels se fait l'affichage
**/

#ifndef _DEBUG_
#define _DEBUG_

#include <stdio.h>


//~ #define DEBUG_COLL 
#define DESACTIVATE_GFX
#define ARG_ANALYSER_ON
#define DEBUG 2
#define TRACE 2
#define TRACE_CONSTR 2	/* En général: 1 pour les classes singletons, 2 pour les classes peu instanciées, 3 pour les classes souvent instanciées */
#define PERF_CYCLES 2
//~ #define ACTIVE_FMOD /* Si desactive, pas de fmod*/

#ifdef WIN32
	#define COL_CONSTR
	#define COL_DEBUG
	#define COL_TRACE
	#define COL_PERF
	#define END_COL
#else
	#define COL_CONSTR "\033[32m"
	#define COL_DEBUG "\033[31m"
	#define COL_TRACE "\033[36m"
	#define COL_PERF "\033[35m"
	#define END_COL  "\033[0m"
#endif

#ifdef DEBUG
	#define PRINT_DEBUG(level, format, args...) \
	if (DEBUG >= level){ \
		fprintf(stderr, COL_DEBUG format END_COL, ##args);          \
		fprintf(stderr, COL_DEBUG " (%s:l%d in %s)"  END_COL , __FILE__, __LINE__, __func__); \
		fprintf(stderr, "\n"); \
	}
#else
	#define PRINT_DEBUG(format, args...)
#endif

#ifdef TRACE
	#define PRINT_TRACE(level, format, args...) \
	if (TRACE >= level) { \
		fprintf(stderr, COL_TRACE format END_COL, ##args);          \
		fprintf(stderr, "\n"); \
	}
#else
	#define PRINT_TRACE(format, args...)
#endif

#ifdef TRACE_CONSTR
	#define  PRINT_CONSTR(level, format, args...) \
	if (TRACE_CONSTR >= level) { \
		fprintf(stderr, COL_CONSTR format END_COL, ##args);          \
		fprintf(stderr, "\n"); \
	}
#else
	#define  PRINT_CONSTR(level, format, args...)
#endif

#ifdef PERF_CYCLES
	#define  PRINT_PERF( format, args...)   \
	if (PERF_CYCLES > 0) { \
		fprintf(stderr, COL_PERF format END_COL, ##args);          \
		fprintf(stderr, "\n"); \
	}
#else
	#define PERF_CYCLES 20
	#define  PRINT_PERF(format, args...)
#endif

#endif

