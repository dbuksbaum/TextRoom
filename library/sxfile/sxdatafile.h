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
#ifndef SXDATAFILE_H
#define SXDATAFILE_H
#include <sxfile.h>
#include <QHash>
#include <QVariant>

class QStringList;
/**
 * A key value pair based data file extension for SxFile.
 * QVariant data types are stored in an associative array.
 */
class SxBasicDataFile : public SxFile
{
	public:
	/**
	* Construct a new basic data file.
	*/
	SxBasicDataFile( QObject *parent = 0 );
	~SxBasicDataFile();

	/**
	* Access a value from the data file based off of the key.  If the key is not
	* present in the data file, then the defaultValue is returned.
	*/
	QVariant value( const QString &key, const QVariant &defaultValue = QVariant() ) const;
	/**
	* Set a valud in the data file based off of a key.  If the key is already
	* present in the file then it is over written, if the key is not present it
	* is created.  In the case that the value is the same as the current value
	* in the data set then the document is not modified.  Setting this value will
	* otherwise cause the modified flag of the datafile to be set.
	*/
	void setValue( const QString &key, const QVariant &value );
	/**
	* Returns if a key is in the current data set.
	*/
	bool hasValue( const QString &key ) const;
	/**
	* Returns a list of all keys in the current data set.
	*/
	QStringList keys( ) const;
	/**
	* Clears the current data file.
	*/
	void clear();

protected:
	virtual bool loadData( QIODevice *iodevice );
	virtual bool saveData( QIODevice *iodevice );
	virtual void initData( );
	QHash<QString,QVariant> m_dataSet;
};

#endif
