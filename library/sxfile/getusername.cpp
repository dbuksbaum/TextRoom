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

#include "getusername.h"

#ifdef Q_OS_UNIX
#include <sys/types.h>
#include <pwd.h>
#endif

#ifdef Q_OS_WIN32
#include <windows.h>
#define INFO_BUFFER_SIZE 3276
#endif

#ifdef Q_OS_UNIX

QString currentUserNameUnix()
{
	passwd *password = getpwuid(geteuid());
	if( password )
		return QString::fromLatin1( password->pw_name );
	else
		return QString();
}

#endif

#ifdef Q_OS_WIN32
QString currentUserNameWin32()
{
	TCHAR  infoBuf[INFO_BUFFER_SIZE];
	DWORD  bufCharCount = INFO_BUFFER_SIZE;

	bufCharCount = INFO_BUFFER_SIZE;
	if( !GetUserName( infoBuf, &bufCharCount ) )
		return QString("Unknown");
	else
	{
#ifdef UNICODE
		return QString::fromUtf16( (ushort*)infoBuf, bufCharCount );
#else
		return QString::fromLocal8Bit( infoBuf, bufCharCount );
#endif
	}
}
#endif

QString currentUserName( )
{
#ifdef Q_OS_UNIX
	return currentUserNameUnix();
#endif

#ifdef Q_OS_WIN32
	return currentUserNameWin32();
#endif
}
