#ifndef _BABAR_CONSTANTS_H_
#define _BABAR_CONSTANTS_H_

#include <string>

#define FOR_EACH_CONST_INT(macro) \
	macro(FULL_SCREEN, 0) \
	macro(WINDOW_WIDTH, 600) \
	macro(WINDOW_HEIGHT, 800) \
	macro(LAST_LEVEL, 5) 
	
#define FOR_EACH_CONST_STRING(macro) \
	macro(TEST_LEVEL, "test.lvl")
	
#define DECLARE_CONST_INT(yop, plop) \
	static int yop;
	
#define DECLARE_CONST_STRING(yop, plop) \
	static std::string yop;


class Analyser;
class Constants {
public:
	static void init();
	FOR_EACH_CONST_INT(DECLARE_CONST_INT)
	FOR_EACH_CONST_STRING(DECLARE_CONST_STRING)
	
protected:
	static void initAux(Analyser &analyser);
};

#endif
