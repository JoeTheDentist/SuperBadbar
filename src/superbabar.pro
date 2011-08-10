#-------------------------------------------------
#
# Project created by berardg 2011-05-17T11:16:03
#
#-------------------------------------------------

QT += network
QT -= qui
#QT -= core

TARGET = superbabar
TEMPLATE = app

win32 {
	LIBS += -L"../lib/SDL/lib" -lSDL -lSDL_image -lSDL_ttf \
                -L"../lib/lib" 	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

        INCLUDEPATH += .
		
        Release:DESTDIR = ./
	Release:OBJECTS_DIR = release/.obj
	Release:MOC_DIR = release/.moc
	Release:RCC_DIR = release/.rcc
	Release:UI_DIR = release/.ui

        Debug:DESTDIR = ./
	Debug:OBJECTS_DIR = debug/.obj
	Debug:MOC_DIR = debug/.moc
	Debug:RCC_DIR = debug/.rcc
	Debug:UI_DIR = debug/.ui
}

unix {
	QT_INSTALL_PREFIX = $$[QT_INSTALL_PREFIX]
	X64 = $$find(QT_INSTALL_PREFIX, 64)
	isEmpty(X64) {		
	  	LIBS += -L"../lib/gcc/x32" 
		QMAKE_LFLAGS_RPATH += -L"../lib/gcc/x32" 
	} else {

	}
	QMAKE_LFLAGS += -g 	
	QMAKE_CFLAGS += -g
	QMAKE_CXXFLAGS += -g

	LIBS += -L"../lib/SDL/lib" -lSDL -lSDL_image -lSDL_ttf \
	../lib/gcc/libfmod.so \
	-L"../lib/gcc/"\
	-lSDL_gfx \
	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	
	
 
	DESTDIR = ./
	OBJECTS_DIR = release/.obj
	MOC_DIR = release/.moc
	RCC_DIR = release/.rcc
	UI_DIR = release/.ui
	
}

INCLUDEPATH += ../lib/include
INCLUDEPATH += "../lib/include/"

SOURCES +=  ./main.cpp \
            ./actors/*.cpp \
            ./AI/*.cpp \
            ./control/*.cpp \
            ./events/*.cpp \
            ./game/*.cpp \
            ./items/*.cpp \
            ./menus/*.cpp \
            ./network/*.cpp \
            ./physic/*.cpp \
            ./players/*.cpp \
            ./sets/*.cpp \
            ./sound/*.cpp \
            ./sprites/*.cpp \
            ./util/*.cpp \
            ./video/*.cpp \
			./video/ressources/*.cpp


HEADERS  += ./actors/*.h \
            ./AI/*.h \
            ./control/*.h \
            ./events/*.h \
            ./game/*.h \
            ./items/*.h \
            ./menus/*.h \
            ./network/*.h \
            ./physic/*.h \
            ./players/*.h \
            ./sets/*.h \
            ./sound/*.h \
            ./sprites/*.h \
            ./util/*.h \
            ./video/*.h \
			./video/ressources/*.h
			
FORMS +=
