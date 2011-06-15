#Makefile fils
#Doit etre appele par le Makefile pere, un niveau au dessus, meme niveau que le repertoire obj/

SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=../$(OBJ_DIR)%.o)

SFML_LIB_REP:= ../../lib/
SFML_INC_REP:= ../../include/
LIB_INC		:= -I$(SFML_INC_REP)
LIB_DYN		:= $(wildcard $(SFML_LIB_REP)$(REP_ARCH)*.so.1.6) $(LIB_DYN)

all: $(OBJ)

../$(OBJ_DIR)%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

../$(OBJ_DIR)%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(CC) $(CFLAGS) $(INCLUDES) -o obj/main.o -c main.cpp;
	$(CC) -o $(EXEC_NAME) $(OBJ_DIR)*.o $(LDFLAGS) $(LIBCOMP)
