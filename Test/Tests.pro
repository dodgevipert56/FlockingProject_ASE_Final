TARGET = FlockingTests
SOURCES += main.cpp \
           ../Flocking/src/Boid.cpp \ 
           ../Flocking/src/Flock.cpp
	   

LIBS += -lgtest
INCLUDEPATH += ../Flocking/include
#QMAKE_CXX = clang++
include($(HOME)/NGL/UseNGL.pri)
cache()
