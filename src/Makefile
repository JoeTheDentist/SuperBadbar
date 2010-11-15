CC = g++
CFLAGS = -Wall  -g
EXEC_NAME = main
INCLUDES = 
LIBS = 
OBJ_FILES =  main.o sprites/sprites.o game/game.o control/keyboard.o video/camera.o video/dashboard.o util/collisions.o game/static_data.o util/analyser.o video/statics.o items/weapons.o video/talks.o  game/dynamic_data.o sound/sound_manager.o sprites/babar.o sprites/monsters.o sprites/projectiles.o sprites/walking_monsters.o events/events.o sound/sound.o events/events_manager.o events/event_weapon.o
INSTALL_DIR = .              
LDFLAGS	= -g -lSDL_ttf -lfreetype -lSDL_image -lfmod

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
