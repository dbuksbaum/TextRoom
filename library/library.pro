include(../project.pri)

SXFeatures += filemanager getuser
TEMPLATE = lib
CONFIG += static staticlib
DESTDIR = $$LIB_DIR 
TARGET = flo
QT += opengl xml

HEADERS += block.h \
           blockpropertymodel.h \
           connector.h \
           copygroupcommand.h \
           createblockcommand.h \
           cutgroupcommand.h \
           deleteblockcommand.h \
           deletegroupcommand.h \
           editblockpropertycommand.h \
           mindmap.h \
           movecommand.h \
           movegroupcommand.h \
           pasteblockcommand.h \
           plaintextedit.h \
           reparentblockcommand.h \
	   blockmimedata.h \
 	   blockremover.h \
           colorbutton.h \
           qscaledsvgitem.h \
           mindmapview.h \
           variantdompath.h \
           documentoptions.h \
           exportinterface.h \
           basicpropertyeditor.h \
           qscaledpixmapitem.h \
 pathshaped.h \
 positionitemscommand.h \
 changecolorgroupcommand.h \
 changefontgroupcommand.h \
 shapeselector.h \
 changeshapegroupcommand.h \
 titleeditor.h \
 floparserobserver.h \
 rotatedproxymodel.h 
SOURCES += block.cpp \
	   floparserobserver.cpp \
           blockpropertymodel.cpp \
           connector.cpp \
           copygroupcommand.cpp \
           createblockcommand.cpp \
           cutgroupcommand.cpp \
           deleteblockcommand.cpp \
           deletegroupcommand.cpp \
           editblockpropertycommand.cpp \
           mindmap.cpp \
           movecommand.cpp \
           movegroupcommand.cpp \
           pasteblockcommand.cpp \
           plaintextedit.cpp \
           reparentblockcommand.cpp \
	   blockmimedata.cpp \
	   blockremover.cpp  \
           colorbutton.cpp \
           qscaledsvgitem.cpp \
           mindmapview.cpp \
           variantdompath.cpp \
           documentoptions.cpp \
           basicpropertyeditor.cpp \
           qscaledpixmapitem.cpp \
 pathshaped.cpp \
 positionitemscommand.cpp \
 changecolorgroupcommand.cpp \
 changefontgroupcommand.cpp \
 shapeselector.cpp \
 changeshapegroupcommand.cpp \
 titleeditor.cpp \
 rotatedproxymodel.cpp 

FORMS += documentoptions.ui \
           contents.ui \
 shapeselector.ui \
 scalewidget.ui

RESOURCES += emblems.qrc \
	images.qrc \
	icons.qrc

include(sxfile/sxfile.pri)
include(qdomutils/domutilsfiles.pri)
include(qmodeladaptor/lib.pri)

