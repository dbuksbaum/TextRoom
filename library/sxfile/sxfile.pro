TEMPLATE = lib
TARGET = sxfile
CONFIG += static debug warn_on
VERSION = 0.99
DESTDIR = $$PWD
OBJECTS_DIR = .obj
MOC_DIR = .moc
SXFeatures += full
include( sxfile.pri )
