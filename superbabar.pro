#-------------------------------------------------
#
# Project created by berardg 2011-05-17T11:16:03
#
#-------------------------------------------------

#QT       += core gui #network
QT -= qui
QT -= core

TARGET = superbabar
TEMPLATE = app

LIBS += -L"lib\SDL\lib" -lSDL -lSDL_image -lSDL_ttf \
        -L"lib\fmodapi375win\api\lib" -lfmod \
        -lglut -lopengl32

SOURCES +=  src/main.cpp \
            src/actors/*.cpp \
            src/AI/*.cpp \
            src/control/*.cpp \
            src/events/*.cpp \
            src/game/*.cpp \
            src/items/*.cpp \
            src/menus/*.cpp \
            #src/network/*.cpp \
            src/physic/*.cpp \
            src/players/*.cpp \
            src/sets/*.cpp \
            src/sound/*.cpp \
            src/sprites/*.cpp \
            src/util/*.cpp \
            src/video/*.cpp

HEADERS  += src/actors/*.h \
            src/AI/*.h \
            src/control/*.h \
            src/events/*.h \
            src/game/*.h \
            src/items/*.h \
            src/menus/*.h \
            #src/network/*.h \
            src/physic/*.h \
            src/players/*.h \
            src/sets/*.h \
            src/sound/*.h \
            src/sprites/*.h \
            src/util/*.h \
            src/video/*.h

FORMS +=
