
export OBJ_DIR=obj/
export CC = g++
export CFLAGS=-g -Wall #$(LIB_INC) 
export LDFLAGS= -g -lSDL_ttf -lfreetype -lSDL_image -lfmod # $(LIB_DYN)

DIR = control events game items menus sound sprites util video AI
EXEC_NAME = babar
DOC_REP = ../doc/doxydoc/
VAL_SUPRESS_FLAG = --suppressions=../utils/valgrind_suppress/BABAR_SDL.supp  --suppressions=../utils/valgrind_suppress/SDL.supp   --suppressions=../utils/valgrind_suppress/other_SDL.supp --suppressions=../utils/valgrind_suppress/fmod.supp  --workaround-gcc296-bugs=yes

all:
	@for i in $(DIR); do \
	$(MAKE) -C $$i all; \
	done
	$(CC) $(CFLAGS) $(INCLUDES) -o obj/main.o -c main.cpp;
	$(CC) -o $(EXEC_NAME) $(OBJ_DIR)*.o $(LDFLAGS)

clean:
	rm $(OBJ_DIR)*.o $(EXEC_NAME)

test:
	./$(EXEC_NAME)
	
go:
	./$(EXEC_NAME)
	
val: 
	valgrind $(VAL_SUPRESS_FLAG) ./$(EXEC_NAME)

valfull: 
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes $(VAL_SUPRESS_FLAG) ./$(EXEC_NAME) -menu
	
profile:
	valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes ./babar yopi

gdb:
	gdb ./$(EXEC_NAME)
	
menu:
	./$(EXEC_NAME) -menu

edit:
	#codeblocks cbShell/Shell.cbp&
	
editTX:
	#kate src/*.h src/*.c&

doc:
	doxygen ../doxy_conf
	
read: 
	firefox $(DOC_REP)html/index.html &
	
########################
## Affichage des warnings de compilation
########################
warn: clean
	@echo
	@echo "##########################"
	@echo "##### WARNINGS ONLY ######"
	@echo "##########################"
	@$(MAKE) 2>&1 >/dev/null | grep --color=auto "warning\|\(style\)" || echo
	
	
########################
## Affichage des taches restantes de compilation
########################
todo:
	@echo "##########################"
	@echo "#### 'TODO' restants #####"
	@echo "##########################"
	@grep --color=auto -rn TODO */* || echo
	
record:
	./babar -record record.rcd
	
replay:
	./babar -replay record.rcd
