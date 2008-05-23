TEMPLATE = app
TARGET = textroom
DEPENDPATH += . resource src ui
INCLUDEPATH += . src
DESTDIR += bin
OBJECTS_DIR += build
MOC_DIR += build
UI_DIR += build
RCC_DIR += build
HEADERS += src/helpdialog.h src/optionsdialog.h src/textroom.h src/searchdialog.h
FORMS += ui/optionsdialog.ui ui/textroom.ui ui/helpdialog.ui
SOURCES += src/helpdialog.cpp \
 src/main.cpp \
 src/optionsdialog.cpp \
 src/textroom.cpp \
 src/searchdialog.cpp
RESOURCES += resource/textroom.qrc
CONFIG += release
RC_FILE = textroom.rc
INSTALLS += data \
 target \
 documentation \
 icon \
 desktop
data.path += /usr/local/share/textroom
data.files = resource/sounds/*
target.path = /usr/local/bin
documentation.path = /usr/local/share/textroom/doc
documentation.files = docs/*
icon.path = /usr/share/pixmaps
icon.files = resource/images/textroom.png
desktop.path = /usr/share/applications
desktop.files = resource/desktop/textroom.desktop
