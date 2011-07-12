#valgrind --leak-check=full --show-reachable=yes --track-origins=yes --gen-suppressions=all ./babar 2>&1 | egrep "^[{}]|^   [^ \t]" > last.supr
INCLUDES_DIR=
export OBJ_DIR=obj/
export CC = g++  
export CFLAGS= -g $(INCLUDES_DIR) -Wall #$(LIB_INC) 
export PROFILEFLAG= -lprofiler
LDFLAGS= -g  -lfreetype -lSDL_image -lSDL_ttf -lglut #-lfmodex-4.34.03 # $(PROFILEFLAG) $(LIB_DYN)
LIBCOMP=  ../lib/gcc/libfmod.so #../lib/fmodex/lib/libfmodex-4.34.03.so   #../lib/gcc/libSDL_ttf.so

DIR = actors control events game items menus players physic sound sprites util video AI sets
EXEC_NAME = babar
DOC_REP = ../doc/doxydoc/
VAL_SUPRESS_FLAG = --suppressions=../utils/valgrind_suppress/BABAR_SDL.supp  --suppressions=../utils/valgrind_suppress/SDL.supp   --suppressions=../utils/valgrind_suppress/other_SDL.supp --suppressions=../utils/valgrind_suppress/fmod.supp  --suppressions=../utils/valgrind_suppress/opengl.supp  --workaround-gcc296-bugs=yes

all:
	@for i in $(DIR); do \
	$(MAKE) -C $$i all; \
	done
	$(CC) $(CFLAGS) $(INCLUDES) -o obj/main.o -c main.cpp;
	$(CC) -o $(EXEC_NAME) $(OBJ_DIR)*.o $(LDFLAGS) $(LIBCOMP)

clean:
	rm $(OBJ_DIR)*.o $(EXEC_NAME)

test:
	./$(EXEC_NAME)
	
go:
	./$(EXEC_NAME)
	
val: 
	valgrind $(VAL_SUPRESS_FLAG) ./$(EXEC_NAME)

valfull: 
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes $(VAL_SUPRESS_FLAG) ./$(EXEC_NAME) 
	
#~ profile:
	#~ valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes ./babar 
	
prof: $(EXEC_NAME)
	@CPUPROFILE=$(EXEC_NAME).profile ./$(EXEC_NAME)
	@./pprof --gv $(EXEC_NAME) $(EXEC_NAME).profile

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
