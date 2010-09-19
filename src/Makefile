CC = g++
CFLAGS = -Wall  -g
EXEC_NAME = main
INCLUDES = 
LIBS =
OBJ_FILES =  main.o sprites.o game.o globals.o keyboard.o camera.o collisions.o static_data.o analyser.o statics.o weapons.o talks.o dynamic_data.o
INSTALL_DIR = .
LDFLAGS	= -g -lSDL_ttf -lfreetype -lSDL_image 

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

test:
	./main
