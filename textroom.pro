TEMPLATE = app
TARGET = textroom
DEPENDPATH += . \
    resource \
    src \
    ui
INCLUDEPATH += . \
    src \
    src/include \
    /usr/include \
    /usr/include/hunspell \
    /usr/include/SDL
DESTDIR += .
OBJECTS_DIR += temp
MOC_DIR += temp
UI_DIR += temp
RCC_DIR += temp
HEADERS += src/include/helpdialog.h \
    src/include/optionsdialog.h \
    src/include/textroom.h \
    src/include/searchdialog.h \
    src/include/font.h \
    src/include/scratchpad.h \
    src/include/about.h
FORMS += ui/optionsdialog.ui \
    src/ui/textroom.ui \
    src/ui/helpdialog.ui \
    src/ui/font.ui \
    src/ui/scratchpad.ui \
    src/ui/about.ui
SOURCES += src/helpdialog.cpp \
    src/main.cpp \
    src/optionsdialog.cpp \
    src/textroom.cpp \
    src/searchdialog.cpp \
    src/font.cpp \
    src/scratchpad.cpp \
    src/about.cpp
RESOURCES += resource/textroom.qrc
CONFIG += release \
    build_all
INSTALLS += data \
    dict \
    target \
    desktop \
    uninstaller \
    mime \
    icon
LIBS = -lSDL \
    -lSDLmain \
    -lSDL_mixer \
    -lhunspell
QT += core \
    gui

data.path = /usr/share/sounds
data.files = resource/sounds/*
target.path = /usr/bin
desktop.path = /usr/share/applications
desktop.files = resource/desktop/textroom.desktop
doc-icon.path = /usr/share/textroom
doc-icon.files = resource/images/textroom-doc.png
mime.path = /usr/share/textroom
mime.files = resource/desktop/textroom-txr-mime.xml
uninstaller.path = /usr/bin
uninstaller.files = resource/desktop/textroom-uninstall
dict.path = /usr/share/myspell/dicts
dict.files = resource/dict/*
icon.path = /usr/share/pixmaps
icon.files = resource/images/textroom.png

unix:system(xdg-icon-resource install --context mimetypes --size 48 ./resource/images/textroom-doc.png application/x-txr)
unix:system(xdg-mime install ./resource/desktop/textroom-txr-mime.xml)
unix:system(xdg-mime default textroom.desktop application/x-txr)	
