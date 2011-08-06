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
	LIBS += -L"../lib/include/"
		
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
	QMAKE_LFLAGS +=	-lsfml-system -lsfml-graphics -lsfml-window
	QMAKE_CFLAGS += 
	QMAKE_CXXFLAGS += 
	
	
	dep.target = dep
	QT_INSTALL_PREFIX = $$[QT_INSTALL_PREFIX]
	X64 = $$find(QT_INSTALL_PREFIX, 64)
	isEmpty(X64) {
	    dep.commands = ./depends.sh
		
	  	LIBS += -L"../lib/gcc/x32" 
		QMAKE_LFLAGS_RPATH += -L"../lib/gcc/x32" 
	} else {
	  dep.commands = export LD_LIBRARY_PATH="../lib/gcc/x64":$LD_LIBRARY_PATH

	}
	QMAKE_EXTRA_UNIX_TARGETS += dep 			
			
	DESTDIR = ./
	OBJECTS_DIR = release/.obj
	MOC_DIR = release/.moc
	RCC_DIR = release/.rcc
	UI_DIR = release/.ui
}

	
INCLUDEPATH += "../lib/include/"

SOURCES +=  ./main.cpp 
           

FORMS +=
