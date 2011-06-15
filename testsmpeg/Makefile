SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)
LDFLAGS= -g  -lfreetype -lSDL_image -lSDL_ttf -lsmpeg#-lfmodex-4.34.03 # $(PROFILEFLAG) $(LIB_DYN)
LIBCOMP=  
CC = g++
CFLAGS= -g -Wall #$(LIB_INC)
EXEC_NAME = babar

all: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o main.o -c main.cpp;
	$(CC) -o $(EXEC_NAME) *.o $(LDFLAGS) $(LIBCOMP)
	
	
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
