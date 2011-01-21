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

#ifndef SXTEXTFILE_H
#define SXTEXTFILE_H

#include <sxfile.h>

/**
 * A SxTextFile is a very simple wrapper that loads and saves latin-8 text.
 */
class SxTextFile : public SxFile
{
public:
	SxTextFile( QObject *parent = 0);
  
	/**
	 * Return the currenly loaded text.
	 */
	QByteArray data() const;
	/**
	 * Set the current file's text content to buffer.  This will flag 
	 * the file as modified and it will not be set to unmodified until 
	 * the file is saved.
	 */
	void setData( const QByteArray &buffer );
	
protected:
  virtual bool loadData( QIODevice *iodevice );
  virtual bool saveData( QIODevice *iodevice );
  virtual void initData( );
	
private:
	QByteArray m_databuffer;
};

#endif
