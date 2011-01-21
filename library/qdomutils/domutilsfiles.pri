INCLUDEPATH += $${PWD}
VPATH += $${PWD}

FORMS += browser_base.ui
HEADERS += node.h \
           elementtools.h \
           dompath.h \
           xmlwalker.h \
           browser.h \
           qdommodel.h

SOURCES += node.cpp \
           elementtools.cpp \
           dompath.cpp \
           xmlwalker.cpp \
           browser.cpp \
	   qdommodel.cpp

QT +=  xml 
