#!/bin/sh

# READ THIS FIRST: run from the top of the svn folder, not from here
rm -rf textroom.app/ textroom.dmg 
make clean 
qmake -spec macx-g++ 
make 
make install
macdeployqt textroom.app -dmg
