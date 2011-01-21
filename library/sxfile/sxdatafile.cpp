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

#include "sxdatafile.h"
#include <QStringList>

SxBasicDataFile::SxBasicDataFile( QObject *parent )
: SxFile( parent )
{

}
SxBasicDataFile::~SxBasicDataFile()
{

}

QVariant SxBasicDataFile::value( const QString &key, const QVariant &defaultValue  ) const
{
  if( hasValue(key) )
    return m_dataSet[key];
  else
    return defaultValue;
}

void SxBasicDataFile::setValue( const QString &key, const QVariant &value )
{
  if( m_dataSet[key] == value )
    return;
  setModified( true );
  m_dataSet[key] = value;
}

bool SxBasicDataFile::hasValue( const QString &key ) const
{
  return m_dataSet.contains(key);
}

QStringList SxBasicDataFile::keys( ) const
{
  return m_dataSet.keys();
}

void SxBasicDataFile::clear()
{
  m_dataSet.clear();
}

bool SxBasicDataFile::loadData( QIODevice * iodevice )
{
	clear();
	QDataStream ds(iodevice);
	ds >> m_dataSet;
	return true;
}

bool SxBasicDataFile::saveData( QIODevice * iodevice )
{
	QDataStream ds( iodevice );
	ds << m_dataSet;
	return true;
}

void SxBasicDataFile::initData( )
{
	clear();
}
