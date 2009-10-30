TEMPLATE = app
TARGET = SRVjoy
QT += core \
    gui
HEADERS += args.h \
    SRVjoy.h
SOURCES += SRVjoy.cpp \
    args.cpp \
    main.cpp
FORMS += 
RESOURCES += playerGUI.qrc
INCLUDEPATH += /usr/local/include/player-2.1/
LIBS += -L/usr/local/lib \
    -lplayerc++
CONFIG += no_keywords
