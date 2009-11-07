TEMPLATE = app
TARGET = SRVjoy
QT += core \
    gui
HEADERS += ImageThread.h \
    args.h \
    SRVjoy.h
SOURCES += ImageThread.cpp \
    SRVjoy.cpp \
    args.cpp \
    main.cpp
FORMS += 
RESOURCES += playerGUI.qrc
INCLUDEPATH += /usr/local/include/player-2.1/ \
    /usr/local/include/player-3.0/
LIBS += -L/usr/local/lib \
    -lplayerc++
CONFIG += no_keywords
