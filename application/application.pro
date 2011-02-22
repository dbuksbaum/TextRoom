include(../project.pri)
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
	    /usr/include/libxml++-2.6 \
	    /usr/include/glibmm-2.4 \
	    /usr/lib/glibmm-2.4/include \
	    /usr/include/glib-2.0 \
	    /usr/lib/glib-2.0/include \
	    /usr/lib/libxml++-2.6/include \
	    /usr/include/SDL
}

macx {
	INCLUDEPATH += . \
	    src \
	    src/include \
	    /usr/include \
	    /usr/include/hunspell \
	    /sw/include/libxml++-2.6 \
            /sw/lib/libxml++-2.6/include \
            /sw/include/glibmm-2.4 \
	    /sw/lib/glibmm-2.4/include \
	    /sw/include/glib-2.0 \
	    /sw/lib/glib-2.0/include
}

win32 {
	 RC_FILE +=  resource/images/textroom.rc
	 CONFIG +=  release  build_all
         LIBS = -lSDL \
              -lSDL_mixer \
              -lhunspell
}

DESTDIR += ..
HEADERS += src/include/helpdialog.h \
    src/include/optionsdialog.h \
    src/include/textroom.h \
    src/include/searchdialog.h \
    src/include/font.h \
    src/include/scratchpad.h \
    src/include/about.h \
    src/include/miniflo.h \
    src/include/asciiexportdialog.h \
    src/include/getaword.h \
    src/include/musicroom.h \
    src/include/googledocs.h \
    src/gdata/atom_helper.h \
    src/gdata/client/doc_list_service.h \
    src/gdata/client/service.h \
    src/gdata/util/string_utils.h \
    src/include/asciireporter.h
FORMS += ui/optionsdialog.ui \
    src/ui/textroom.ui \
    src/ui/helpdialog.ui \
    src/ui/font.ui \
    src/ui/scratchpad.ui \
    src/ui/about.ui \
    src/ui/miniflo.ui \
    src/ui/getaword.ui \
    src/ui/musicroom.ui \
    src/ui/googledocs.ui \
    src/ui/asciiexport.ui
SOURCES += src/helpdialog.cpp \
    src/main.cpp \
    src/optionsdialog.cpp \
    src/textroom.cpp \
    src/searchdialog.cpp \
    src/font.cpp \
    src/scratchpad.cpp \
    src/about.cpp \
    src/miniflo.cpp \
    src/asciiexportdialog.cpp \
    src/getaword.cpp \
    src/musicroom.cpp \
    src/googledocs.cpp \
    src/gdata/atom_helper.cc \
    src/gdata/client/doc_list_service.cc \
    src/gdata/client/service.cc \
    src/gdata/util/string_utils.cc \
    src/asciireporter.cpp
RESOURCES += resource/textroom.qrc \
	resource/images/icons-app.qrc 
linux-g++ {
    CONFIG += release \
        build_all
    INSTALLS += data \
        dict \
        target \
        desktop \
        uninstaller \
        mime \
	words \
        icon
    LIBS = -lSDL_mixer \
	-lSDL \
        -lhunspell \
	-lglibmm-2.4 \
	-lcurl \
	-lxml++-2.6 \
	$$TOPDIR/lib/libflo.a
    data.path = /usr/share/sounds
    data.files = resource/sounds/*
    target.path = /usr/bin
    words.path = /usr/share/textroom
    words.files = resource/words.txt
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
        build_all

    QMAKE_LFLAGS += -F/Library/Frameworks/SDL.framework \
        -F/Library/Frameworks/SDL_mixer.framework

    LIBS += -framework SDL \
        -framework SDL_mixer \
	-lcurl \
        -lhunspell-1.2 \
	-L/sw/lib -lxml++-2.6 \
	-lglibmm-2.4 \
	-lglib-2.0 \
	$$TOPDIR/lib/libflo.a

    RC_FILE=MacOS/resource/textroom.icns
    QMAKE_MACOSX_DEPLOYMENT_TARGET=10.6
    QMAKE_POST_LINK=strip $$TOPDIR/textroom.app/Contents/MacOS/textroom
    QMAKE_INFO_PLIST=MacOS/resource/Info.plist

    INSTALLS += sounds \ 
	dict \
	sdl \
	sdl_mixer \
	mikmod \
	smpeg \
        words

    sdl.path = $$TOPDIR/textroom.app/Contents/Frameworks/SDL.framework/Versions/A
    sdl.files = /Library/Frameworks/SDL.framework/Versions/A/SDL

    sdl_mixer.path = $$TOPDIR/textroom.app/Contents/Frameworks/SDL_mixer.framework/Versions/A
    sdl_mixer.files = /Library/Frameworks/SDL_mixer.framework/Versions/A/SDL_mixer

    mikmod.path = $$TOPDIR/textroom.app/Contents/Frameworks/SDL_mixer.framework/Versions/A/Frameworks/mikmod.framework/Versions/A
    mikmod.files = /Library/Frameworks/SDL_mixer.framework/Frameworks/mikmod.framework/Versions/A/mikmod

    smpeg.path = $$TOPDIR/textroom.app/Contents/Frameworks/SDL_mixer.framework/Versions/A/Frameworks/smpeg.framework/Versions/A
    smpeg.files = /Library/Frameworks/SDL_mixer.framework/Frameworks/smpeg.framework/Versions/A/smpeg

    dict.path = $$TOPDIR/textroom.app/Contents/Resources/dict
    dict.files = resource/dict/* MacOS/resource/dict/*

    sounds.path = $$TOPDIR/textroom.app/Contents/Resources/sounds
    sounds.files = resource/sounds/*

    words.path = $$TOPDIR/textroom.app/Contents/Resources/words
    words.files = resource/words.txt
}

QT += core \
    gui \
    svg \
    opengl \
    xml

linux-g++:system(xdg-icon-resource install --context mimetypes --size 48 ./resource/images/textroom-doc.png application/x-txr)
linux-g++:system(xdg-mime install ./resource/desktop/textroom-txr-mime.xml)
linux-g++:system(xdg-mime default textroom.desktop application/x-txr)	
