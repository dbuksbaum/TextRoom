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

#include "sxtextfile.h"

#include <QTextStream>


SxTextFile::SxTextFile( QObject *parent)
:SxFile(parent)
{

}

bool SxTextFile::loadData( QIODevice *iodevice )
{
	m_databuffer = iodevice->readAll();
	return true;
}

bool SxTextFile::saveData( QIODevice *iodevice )
{
	QTextStream ts(iodevice);
	ts << m_databuffer;
	return true;
}

void SxTextFile::initData( )
{
	m_databuffer.clear();
	setModified(false);
}

QByteArray SxTextFile::data() const
{
	return m_databuffer;
}

void SxTextFile::setData( const QByteArray &buffer )
{
	m_databuffer = buffer;
	setModified(true);
}
