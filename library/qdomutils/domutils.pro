include(../qdomtools_build.pri)
win32:TARGETDEPS -= $$TOPDIR/tools/xmlc/xmlc.exe
unix:TARGETDEPS -= $$TOPDIR/tools/xmlc/xmlc

unix:TARGETDEPS -= $$TOPDIR/domutils/libdomutils.a
win32:TARGETDEPS -= $$TOPDIR/domutils/domutils.lib
LIBS -= -ldomutils


CONFIG +=  staticlib
TEMPLATE = lib

DESTDIR = $$PWD
CONFIG += create_prl

include(domutilsfiles.pri)
