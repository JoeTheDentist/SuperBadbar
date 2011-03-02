#Makefile fils
#Doit etre appele par le Makefile pere, un niveau au dessus, meme niveau que le repertoire obj/

SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=../$(OBJ_DIR)%.o)


all: $(OBJ)

../$(OBJ_DIR)%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

../$(OBJ_DIR)%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

