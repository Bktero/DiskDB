######################################################################
# Automatically generated by qmake (2.01a) mar. 26. juil. 08:34:05 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . headers sources
INCLUDEPATH += . headers sources

QT += sql

CONFIG -= debug debug_and_release_target DebugBuild Debug debug_and_release
message(Valeur de CONFIG = $$CONFIG)

DESTDIR = release

# Input
HEADERS += headers/messagesUtilisateur.h \
           headers/myAboutTab.h \
           headers/myAddTab.h \
           headers/myMainWindow.h \
           headers/mySearchTab.h \
           headers/mySQL.h \
           headers/myWelcomeTab.h
SOURCES += sources/main.cpp \
           sources/myAboutTab.cpp \
           sources/myAddTab.cpp \
           sources/myMainWindow.cpp \
           sources/mySearchTab.cpp \
           sources/mySQL.cpp \
           sources/myWelcomeTab.cpp
