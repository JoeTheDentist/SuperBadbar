/**
 * 	@file debug.h
 * 	@brief Macros de debug / traces pour le développement
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 * Trois macros de debug et une de performance:
 * PRINT_CONSTR pour tracer les constructeurs et destructeurs,
 * PRINT_TRACE pour tracer le reste
 * PRINT_DEBUG  pour du debugage localisé et pour les messages d'erreurs classiques
 * Chacune utilise une constante définie dans ce fichier afin de déterminer la
 * précision des messages: 0 pour n'afficher aucun message, 3 pour afficher le maximum
 * de messages.
 * Ces messages ne doivent pas apparaitre dans le projet final et servent seulement à suivre
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

#define _OPENGL_ACTIVE_

//~ #define DEBUG_COLL 1
#define ARG_ANALYSER_ON
#define DEBUG 2
#define TRACE 2
#define TRACE_CONSTR 2 	/* En général: 1 pour les classes singletons, 2 pour les classes peu instanciées, 3 pour les classes souvent instanciées */
#define PERF_CYCLES 2



//~ #define DEBUG_COLL


#ifdef WIN32
	#ifdef DEBUG
		#define PRINT_DEBUG(level, format, args...)\
		if (DEBUG >= level) { \
			fprintf(stderr,format, ##args);    \
			fprintf(stderr, "\n"); \
		}
	#else
		#define PRINT_DEBUG(format, args...)
	#endif

	#ifdef TRACE
		#define PRINT_TRACE(level, format, args...) \
		if (TRACE >= level) { \
			fprintf(stderr,format, ##args);    \
			fprintf(stderr, "\n"); \
		}
	#else
		#define PRINT_TRACE(format, args...)
	#endif

	#ifdef TRACE_CONSTR
		#define  PRINT_CONSTR(level, format, args...)\
		if (TRACE_CONSTR >= level) { \
			fprintf(stderr,format, ##args);    \
			fprintf(stderr, "\n"); \
		}
	#else
		#define  PRINT_CONSTR(level, format, args...)
	#endif

	#ifdef PERF_CYCLES
		#define  PRINT_PERF( format, args...)  \
		if (PERF_CYCLES > 0) { \
			fprintf(stderr,format, ##args);    \
			fprintf(stderr, "\n"); \
		}
	#else
		#define  PRINT_PERF(format, args...)
	#endif
#else
	#ifdef DEBUG
		#define PRINT_DEBUG(level, format, args...) \
		if (DEBUG >= level){ \
			fprintf(stderr, "\033[31m"format"\033[0m", ##args);          \
			fprintf(stderr, "\n"); \
		}
	#else
		#define PRINT_DEBUG(format, args...)
	#endif

	#ifdef TRACE
		#define PRINT_TRACE(level, format, args...) \
		if (TRACE >= level) { \
			fprintf(stderr, "\033[36m"format"\033[0m", ##args);          \
			fprintf(stderr, "\n"); \
		}
	#else
		#define PRINT_TRACE(format, args...)
	#endif

	#ifdef TRACE_CONSTR
		#define  PRINT_CONSTR(level, format, args...) \
		if (TRACE_CONSTR >= level) { \
			fprintf(stderr, "\033[32m"format"\033[0m", ##args);          \
			fprintf(stderr, "\n"); \
		}
	#else
		#define  PRINT_CONSTR(level, format, args...)
	#endif

	#ifdef PERF_CYCLES
		#define  PRINT_PERF( format, args...)   \
		if (PERF_CYCLES > 0) { \
			fprintf(stderr, "\033[35m"format"\033[0m", ##args);          \
			fprintf(stderr, "\n"); \
		}
	#else
		#define PERF_CYCLES 20
		#define  PRINT_PERF(format, args...)
	#endif
#endif











#endif

