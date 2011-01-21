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
#ifndef VERSION_UTILS_H
#define VERSION_UTILS_H

#include <QString>
class QFile;
class VersionUtilsPrivate;
class VersionUtils
{
public:
	VersionUtils( );
	~VersionUtils( );
	bool binaryPatchQFile( QFile *input, QFile *patch, QFile *output );
	bool binaryDiffQFiles( QFile *inputA, QFile *inputB, QFile *patch );

	bool binaryDiffFiles( const QString &fileOne, const QString &fileTwo, const QString &output );
	bool binaryPatchFile( const QString &source, const QString &patch, const QString &output );

	bool diffQFiles( QFile *inputA, QFile *inputB, QFile *patch );
	bool patchQFile( QFile *input, QFile *patch, QFile *output, QFile *reject );

	bool diffFiles( const QString &fileOne, const QString &fileTwo, const QString &output );
	bool patchFile( const QString &fileOne, const QString &patch, const QString &result, const QString &reject = QString());

	bool filesIdentical( const QString &fileOne, const QString &fileTwo );

private:
	VersionUtilsPrivate *d_ptr;
	Q_DECLARE_PRIVATE( VersionUtils );
};

#endif
