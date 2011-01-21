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

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QStringList>

class QVariant;

class Option
{
public:
	enum Type {Invalid = 0, Argument, Flag, Other };
	Option(  );
	Option( const QString &argument );

	QString name( ) const;
	QString value( ) const;
	Type type( ) const;
private:
	QString m_name;
	QString m_value;
};

/**
* A single command line argument definition.
* @code
*	CmdLineArg cmdLineArgs[] = {
*		{ tr("arg"), Option::Argument, true, tr("some argument") },
*		{ tr("opt"), Option::Flag, false, tr("some argument") },
*		{ 0, Option::Invalid, 0, 0 }
*		};
*	CommandLine cmdLine( cmdLineArgs );
* @endcode
*/
struct CmdLineArg
{
	QString name;
	Option::Type type;
	bool required;
	QString description;
};

/**
* A command line parser class.
* Supported notation:
* @li /flag
* @li -flag
* @li --flag
* @li /arg=value
* @li -arg=value
* @li --arg=value
* @li /arg:value
* @li -arg:value
* @li --arg:value
* @li /arg value
* @li -arg value
* @li --arg value
* @li a list of files.
*
*/
class CommandLine
{
public:
	CommandLine( const QStringList &args, CmdLineArg *argDefs );
	/**
	* Convience constructor that gets its arguments from
	* QCoreApplication::arguments(). This is useful when you
	* wish to handle command line arguments outside of the
	* int main() method.
	*/
	CommandLine( CmdLineArg *argDefs );
	bool argumentsValid( ) const;
	bool hasArgument( const QString &arg ) const;
	bool hasFlag( const QString &flag ) const;
	QVariant argument( const QString &arg ) const;
	QString help( ) const;
	QStringList files( ) const;

private:
	Option::Type argumentType( const QString &arg ) const;
	Option findOption( const QString &name, Option::Type type ) const;
	void initArgs( const QStringList &args );
	CmdLineArg *m_argDefs;
	QList<Option> m_options;
	QStringList m_files;
};

#endif
