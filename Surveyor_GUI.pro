TEMPLATE = app
TARGET = Surveyor_GUI
QT += core \
    gui
HEADERS += SRVjoy.h
SOURCES += SRVjoy.cpp \
    main.cpp
FORMS += 
RESOURCES += playerGUI.qrc
INCLUDEPATH += /usr/local/include/player-2.1/
LIBS += -L/usr/local/lib \
    -lplayerc++
