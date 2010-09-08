#ifndef _DEBUG_
#define _DEBUG_

/**
 * Trois macros de debug: une pour tracer les constructeurs et destructeurs, 
 * une pour tracer le reste, une pour du debugage localisé
 * Chacune utilise une constante définie dans ce fichier afin de déterminer la 
 * précision des messages: 0 pour n'afficher aucun message, 3 pour afficher le maximum 
 * de messages. 
 * Ces messages ne doivent pas apparaitre dans le projet final et servent seulement à suivre
 * le comportement du programme.
**/


#define DEBUG 3
#define TRACE 3
#define TRACE_CONSTR 3
#define PERF_CYCLES 5


#ifdef DEBUG
	#define PRINT_DEBUG(level, format, args...) if (DEBUG >= level) \
	fprintf(stderr, "\033[31m"format"\033[0m", ##args);        
#else
	#define PRINT_DEBUG(format, args...) 
#endif


#ifdef TRACE
	#define PRINT_TRACE(level, format, args...) if (TRACE >= level) \
	fprintf(stderr, "\033[36m"format"\033[0m", ##args);        
#else
	#define PRINT_DEBUG(format, args...) 
#endif


#ifdef TRACE_CONSTR
	#define  PRINT_CONSTR(level, format, args...) if (TRACE_CONSTR >= level) \
	fprintf(stderr, "\033[32m"format"\033[0m", ##args);
#else
	#define  PRINT_CONSTR(level, format, args...)
#endif


/**
 * PRINT_PERF():  macro utilisée par Game pour afficher 
 * le pourcentage de cpu utilisé par le programme sur un tour
 * de jeu
 * La constante PERF_CYCLES correspond au nombre de cycles 
 * entre lesquels se fait l'affichage
**/


#endif

