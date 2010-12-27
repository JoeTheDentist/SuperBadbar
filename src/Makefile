
export OBJ_DIR=obj/
export CC = g++
export CFLAGS=-g -Wall $(LIB_INC) 
export LDFLAGS= -g -lSDL_ttf -lfreetype -lSDL_image -lfmod  $(LIB_DYN)

DIR = control events game items sound sprites util video
EXEC_NAME = babar
DOC_REP = ../doc/
VAL_SUPRESS_FLAG = --suppressions=../utils/valgrind_suppress/BABAR_SDL.supp  --suppressions=../utils/valgrind_suppress/SDL.supp   --suppressions=../utils/valgrind_suppress/other_SDL.supp 



ARCH		:= $(shell uname -m)
ifneq (,$(findstring i686,$(ARCH)))
REP_ARCH	:= x32/
else ifneq (,$(findstring x86_64,$(ARCH)))
REP_ARCH	:= x64/
else
WARN_ARCH	:= \n\
+++ Architecture non supportée\n
endif

ifeq (,$(findstring dev/lib/x,${LD_LIBRARY_PATH}))
WARN_SFML	:= \n\
+++	Pour éviter un crash à l'éxécution, configurez votre .bashrc avec la commande suivante :\n\
+++	echo 'export LD_LIBRARY_PATH='${LD_LIBRARY_PATH}':'`pwd`'/lib/'$(REP_ARCH) >> ~/.bashrc ; . ~/.bashrc\n
endif

SFML_LIB_REP:= ../lib/
SFML_INC_REP:= ../include/
LIB_INC		:= -I$(SFML_INC_REP)
LIB_DYN		:= $(wildcard $(SFML_LIB_REP)$(REP_ARCH)*.so.1.6)


all:
	@for i in $(DIR); do \
	$(MAKE) -C $$i all; \
	done
	#$(MAKE) -C $(DIR) $@
	$(CC) $(CFLAGS) $(INCLUDES) -o obj/main.o -c main.cpp;
	$(CC) -o $(EXEC_NAME) $(OBJ_DIR)*.o $(LDFLAGS)

clean:
	rm $(OBJ_DIR)*.o $(EXEC_NAME)

test:
	./$(EXEC_NAME)
	
val: 
	valgrind $(VAL_SUPRESS_FLAG) ./$(EXEC_NAME)

valfull: 
	valgrind --leak-check=full --show-reachable=yes $(VAL_SUPRESS_FLAG) ./$(EXEC_NAME) 
	
profile:
	valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes ./babar yopi

edit:
	#codeblocks cbShell/Shell.cbp&
	
editTX:
	#kate src/*.h src/*.c&

doc:
	doxygen ../doxy_conf
	
read: 
	firefox $(DOC_REP)html/index.html &
