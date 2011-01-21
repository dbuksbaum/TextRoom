XDIFF_VERSION = 0.14

HEADERS += xadler32.h \
           xbdiff.h \
           xdiff.h \
           xdiffi.h \
           xemit.h \
           xinclude.h \
           xmacros.h \
           xmissing.h \
           xprepare.h \
           xtypes.h \
           xutils.h
SOURCES += xadler32.c \
           xalloc.c \
           xbdiff.c \
           xbpatchi.c \
           xdiffi.c \
           xemit.c \
           xmerge3.c \
           xmissing.c \
           xpatchi.c \
           xprepare.c \
           xutils.c \
           xversion.c

unix:DEFINES += HAVE_UNISTD_H

DEFINES += PACKAGE_VERSION=\"$${XDIFF_VERSION}\" HAVE_STDIO_H HAVE_STDLIB_H HAVE_STRING_H\
	HAVE_LIMITS_H HAVE_MEMCHR HAVE_MEMCMP HAVE_MEMCPY HAVE_MEMSET HAVE_STRLEN

OBJECTS_DIR = .obj

VPATH += $${PWD}
DEPENDPATH += $${PWD}
INCLUDEPATH += $${PWD}