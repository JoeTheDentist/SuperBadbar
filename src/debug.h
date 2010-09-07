#ifndef _DEBUG_
#define _DEBUG_

#define DEBUG 0
#ifdef DEBUG
#define PRINT_DEBUG(level, format, args...) if (DEBUG >= level) \
																	fprintf(stderr, "\033[31m"format"\033[0m", ##args);
#else
#define PRINT_DEBUG(format, args...) 
#endif

#endif