TEMPLATE = app
TARGET = textroom
DEPENDPATH += . \
    resource \
    src \
    ui

linux-g++ {
	INCLUDEPATH += . \
	    src \
	    src/include \
	    /usr/include \
	    /usr/include/hunspell \
	    /usr/include/SDL
	
}

macx {
	INCLUDEPATH += . \
	    src \
	    src/include \
	    /usr/include \
	    /usr/include/hunspell \
}

win32 {
	INCLUDEPATH += . \
	     src \
 	     src/include \
	     "C:\Qt\2010.02.1\mingw\include" \
 	     "C:\Qt\2010.02.1\mingw\include\hunspell" \
	 RC_FILE +=  resource/images/textroom.rc
	 CONFIG +=  release  build_all
         LIBS = -lSDL \
              -lSDL_mixer \
              -lhunspell
}

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

linux-g++ {
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
        -lSDL_mixer \
        -lhunspell
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
    dict.path = /usr/share/hunspell
    dict.files = resource/dict/*
    icon.path = /usr/share/pixmaps
    icon.files = resource/images/textroom.png
}

macx {
    CONFIG += release \
        build_all \

    QMAKE_LFLAGS += -F/Library/Frameworks/SDL.framework \
        -F/Library/Frameworks/SDL_mixer.framework

    LIBS += -framework SDL \
        -framework SDL_mixer \
        -lhunspell-1.2 

    RC_FILE=MacOS/resource/textroom.icns
    QMAKE_MACOSX_DEPLOYMENT_TARGET=10.6
    QMAKE_POST_LINK=strip textroom.app/Contents/MacOS/textroom
    QMAKE_INFO_PLIST=MacOS/resource/Info.plist

    INSTALLS += sounds \ 
	dict \
	sdl \
	sdl_mixer \
	mikmod \
	smpeg

    sdl.path = textroom.app/Contents/Frameworks/SDL.framework/Versions/A
    sdl.files = /Library/Frameworks/SDL.framework/Versions/A/SDL

    sdl_mixer.path = textroom.app/Contents/Frameworks/SDL_mixer.framework/Versions/A
    sdl_mixer.files = /Library/Frameworks/SDL_mixer.framework/Versions/A/SDL_mixer

    mikmod.path = textroom.app/Contents/Frameworks/SDL_mixer.framework/Versions/A/Frameworks/mikmod.framework/Versions/A
    mikmod.files = /Library/Frameworks/SDL_mixer.framework/Frameworks/mikmod.framework/Versions/A/mikmod

    smpeg.path = textroom.app/Contents/Frameworks/SDL_mixer.framework/Versions/A/Frameworks/smpeg.framework/Versions/A
    smpeg.files = /Library/Frameworks/SDL_mixer.framework/Frameworks/smpeg.framework/Versions/A/smpeg

    dict.path = textroom.app/Contents/Resources/dict
    dict.files = resource/dict/* MacOS/resource/dict/*

    sounds.path = textroom.app/Contents/Resources/sounds
    sounds.files = resource/sounds/*
}

QT += core \
    gui

linux-g++:system(xdg-icon-resource install --context mimetypes --size 48 ./resource/images/textroom-doc.png application/x-txr)
linux-g++:system(xdg-mime install ./resource/desktop/textroom-txr-mime.xml)
linux-g++:system(xdg-mime default textroom.desktop application/x-txr)	
