DEPENDPATH += $${PWD}
INCLUDEPATH += $${PWD}
VPATH += $${PWD}

contains( SXFeatures, full ){
    SXFeatures += filemanager getuser cmdline
}

contains( SXFeatures, vcs  ){
    message( "Adding version control support..." )
    HEADERS += sxrevfile.h
    SOURCES += sxrevfile.cpp
    include( xdiff/xdiff.pri )
    SXFeatures += versionutils filemanager getuser
}

contains( SXFeatures, versionutils ){
    message( "Adding xdiff support..." )
    HEADERS += versionutils.h
    SOURCES += versionutils.cpp
}

contains( SXFeatures, filemanager ){
    message( "Adding filemanger support..." )
    HEADERS += sxfile.h sxdatafile.h sxbinarydatafile.h sxtextfile.h
    SOURCES += sxfile.cpp sxdatafile.cpp sxbinarydatafile.cpp sxtextfile.cpp
}

contains( SXFeatures, cmdline ){
    message( "Adding commandline features..." )
    HEADERS += commandline.h
    SOURCES += commandline.cpp
}

contains( SXFeatures, getuser ){
    message( "Adding get user support..." )
    HEADERS += getusername.h
    SOURCES += getusername.cpp
    DEFINES += WITH_GETUSER
    win32: LIBS += -lAdvapi32
}
