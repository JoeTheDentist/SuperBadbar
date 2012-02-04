

HEADERS += $$mypath/window/QGLWindow.h \
    $$mypath/window/Renderer.h \
    $$mypath/graphics/Drawable.h \
    $$mypath/graphics/Picture.h \
    $$mypath/utils/Point2f.h \
    $$mypath/graphics/SizedDrawable.h \
    $$mypath/graphics/Texture.h \
    $$mypath/utils/paths.h \
    $$mypath/utils/Sized.h \
    $$mypath/utils/Positionned.h \
    $$mypath/utils/Color.h \
    $$mypath/graphics/Text.h \
    $$mypath/events/InputsManager.h \
    $$mypath/events/Input.h

SOURCES += $$mypath/window/QGLWindow.cpp \
    $$mypath/window/Renderer.cpp \
    $$mypath/graphics/Drawable.cpp \
    $$mypath/graphics/Picture.cpp \
    $$mypath/utils/Point2f.cpp \
    $$mypath/graphics/SizedDrawable.cpp \
    $$mypath/graphics/Texture.cpp \
    $$mypath/utils/Sized.cpp \
    $$mypath/utils/Positionned.cpp \
    $$mypath/utils/Color.cpp \
    $$mypath/graphics/Text.cpp \
    $$mypath/events/InputsManager.cpp \
    $$mypath/events/Input.cpp
QT += opengl

INCLUDEPATH += $$mypath/
