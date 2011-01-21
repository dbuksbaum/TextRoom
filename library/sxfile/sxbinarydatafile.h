/*
    Copyright (C) SourceXtreme, Inc. <oss@sourcextreme.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef SXBINARYDATAFILE_H
#define SXBINARYDATAFILE_H

#include <sxdatafile.h>

/**
 * A SxDataFile that stores the data as a blob of binary data.  This version is compatible with
 * all Qt 4.0 versions.
 */
class SxBinaryDataFile : public SxBasicDataFile
{
public:
  SxBinaryDataFile( QObject *parent = 0);
  
protected:
  virtual bool loadData( QIODevice *iodevice );
  virtual bool saveData( QIODevice *iodevice );
  virtual void initData( );
};

#endif
