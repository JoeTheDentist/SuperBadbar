
export OBJ_DIR=obj/
export CC = g++
export CFLAGS=-g -Wall
export LDFLAGS= -g -lSDL_ttf -lfreetype -lSDL_image -lfmod

DIR = control events game items sound sprites util video
EXEC_NAME = babar


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

edit:
	#codeblocks cbShell/Shell.cbp&
	
editTX:
	#kate src/*.h src/*.c&
