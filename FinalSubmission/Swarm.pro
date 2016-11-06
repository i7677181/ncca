#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T16:07:50
#
#-------------------------------------------------

 QT+=gui opengl core


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

dir = Swarm
TEMPLATE = app

MOC_DIR = moc

OBJECTS_DIR = obj

CONFIG-=app_bundle

UI_HEADERS_DIR+=ui

UI_DIR+=ui

SOURCES+= src/*.cpp \

HEADERS+= include/*.h \

INCLUDEPATH +=./include\

OTHER_FILES += shaders/*.glsl \
          += ui/

DESTDIR=./
FORMS += ui/*.ui

#NGL
!equals(PWD, $${OUT_PWD}){
        copydata.commands = echo "creating destination dirs" ;
        # now make a dir
        copydata.commands += mkdir -p $$OUT_PWD/shaders ;
        copydata.commands += echo "copying files" ;
        # then copy the files
        copydata.commands += $(COPY_DIR) $$PWD/shaders/* $$OUT_PWD/shaders/ ;
        # now make sure the first dir is built before copy
        first.depends = $(first) copydata
        export(first.depends)
        export(copydata.commands)
        # now add it as an extra dir
        QMAKE_EXTRA_dirS += first copydata
}
# use this to suppress some warning from boost
unix*:QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
# basic compiler flags (not all appropriate for all platforms)
QMAKE_CXXFLAGS+= -msse -msse2 -msse3 -std=c++11
macx:QMAKE_CXXFLAGS+= -arch x86_64
macx:INCLUDEPATH+=/usr/local/include/
linux-g++:QMAKE_CXXFLAGS +=  -march=native -std=c++11
linux-g++-64:QMAKE_CXXFLAGS +=  -march=native -std=c++11
# define the _DEBUG flag for the graphics lib
DEFINES +=NGL_DEBUG

unix:LIBS += -L/usr/local/lib
# add the ngl lib
unix:LIBS +=  -L/$(HOME)/NGL/lib -l NGL

# now if we are under unix and not on a Mac (i.e. linux)
linux-*{
                linux-*:QMAKE_CXXFLAGS +=  -march=native
                DEFINES += LINUX
}
DEPENDPATH+=include
# if we are on a mac define DARWIN
macx:DEFINES += DARWIN
# this is where to look for includes
!win32:INCLUDEPATH += $$(HOME)/NGL/include/

win32: {
        PRE_dirDEPS+=C:/NGL/lib/NGL.lib
        INCLUDEPATH+=-I c:/boost
        INCLUDEPATH+=$$(HOMEDRIVE)/NGL/include/
        DEFINES+=GL42
        DEFINES += WIN32
        DEFINES+=_WIN32
        DEFINES+=_USE_MATH_DEFINES
        LIBS+= -lopengl32
        LIBS += -LC:/NGL/lib/ -lNGL
        DEFINES+=NO_DLL
}
