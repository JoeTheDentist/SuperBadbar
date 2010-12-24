
export OBJ_DIR=obj/
export CC = g++
export CFLAGS=-g -Wall
export LDFLAGS= -g -lSDL_ttf -lfreetype -lSDL_image -lfmod

DIR = control events game items sound sprites util video
EXEC_NAME = babar
DOC_REP = ../doc/

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
	valgrind ./$(EXEC_NAME)

valfull: 
	valgrind --leak-check=full --show-reachable=yes ./$(EXEC_NAME) 

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
