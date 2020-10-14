TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    abstract.cpp \
    attacklistener.cpp \
    character.cpp \
    characterdeathlistener.cpp \
    damagelistener.cpp \
    defeatlistener.cpp \
    derived.cpp \
    enemy.cpp \
    enterroomlistener.cpp \
    eventmanager.cpp \
    exitlistener.cpp \
    game.cpp \
    golistener.cpp \
    hintlistener.cpp \
    infolistener.cpp \
    inputlistener.cpp \
    item.cpp \
    main.cpp \
    maplistener.cpp \
    restartlistener.cpp \
    room.cpp \
    takelistener.cpp \
    teleportlistener.cpp \
    victorylistener.cpp

DISTFILES += \
    main.txt

HEADERS += \
    abstract.h \
    attacklistener.h \
    character.h \
    characterdeathlistener.h \
    damagelistener.h \
    defeatlistener.h \
    derived.h \
    enemy.h \
    enterroomlistener.h \
    eventlistener.h \
    eventmanager.h \
    exitlistener.h \
    game.h \
    golistener.h \
    hintlistener.h \
    infolistener.h \
    inputlistener.h \
    item.h \
    maplistener.h \
    restartlistener.h \
    room.h \
    takelistener.h \
    teleportlistener.h \
    victorylistener.h
