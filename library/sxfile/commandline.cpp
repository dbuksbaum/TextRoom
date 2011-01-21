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

#include "commandline.h"
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QApplication>

Option::Option(  )
{

}

bool isNotSwitch( const QString &arg )
{
	if( arg.startsWith( "-" ) )
		return false;
	if( arg.startsWith( "/" ) )
		return false;
	return true;
}

Option::Option( const QString &argument )
{
	if( isNotSwitch( argument ) )
	{
		m_value = argument;
		return;
	}
	QRegExp spliter("^-{1,2}|^/|=|:");
	QStringList arguments = argument.split( spliter,QString::SkipEmptyParts );
	if( arguments.size() > 0)
	 	m_name = arguments.at(0);
	if( arguments.size() > 1 )
		m_value = arguments.at(1);
}

QString Option::name( ) const
{
	return m_name;
}

QString Option::value( ) const
{
	return m_value;
}

Option::Type Option::type( ) const
{
	if( m_name.isEmpty() && m_value.isEmpty())
		return Invalid;
	if( m_value.isEmpty() )
		return Flag;
	if( m_name.isEmpty() )
		return Other;
	return Argument;
}

void CommandLine::initArgs( const QStringList &args )
{
	QString argTemplate = "-%1=%2";
	Option lastOpt;
	bool needsMore = false;
	foreach( QString arg, args )
	{
		Option option( arg );
		Option::Type type;
		if( option.name().isEmpty() )
			type = argumentType( option.value() );
		else
			type = argumentType( option.name() );
		if( type == Option::Other && !isNotSwitch( arg ) )
			type = Option::Invalid;

		if( needsMore )
		{
			QString newArg = argTemplate
					.arg( lastOpt.name() )
					.arg( option.value() );
			option = Option(newArg);
			m_options << option;
			needsMore = false;
		}
		else if( type == Option::Argument )
		{
			if( option.type() != Option::Argument )
			{
				needsMore = true;
				lastOpt = option;
			}
			else
			{
				needsMore = false;
				m_options << option;
			}
		}
		else if ( type == Option::Flag )
		{
			m_options << option;
		}
		else if ( type == Option::Other )
		{
			m_files << arg;
		}
		else
		{
			m_options << option;
		}
	}
}

CommandLine::CommandLine( CmdLineArg *argDefs )
	: m_argDefs(argDefs)
{
	initArgs( QCoreApplication::arguments () );
}

CommandLine::CommandLine( const QStringList &args, CmdLineArg *argDefs )
	: m_argDefs(argDefs)
{
	initArgs( args );
}

bool CommandLine::argumentsValid( ) const
{
	int index = 0;
	QStringList requiredArguments;
	QStringList normalArguments;
	while( m_argDefs[index].name != 0 )
	{
		if( m_argDefs[index].required )
			requiredArguments << m_argDefs[index].name;
		normalArguments << m_argDefs[index].name;
		++index;
	}

	foreach( Option option, m_options )
	{
		if( normalArguments.contains( option.name() ))
			requiredArguments.removeAll( option.name() );
		else
			return false;
	}

	if( requiredArguments.size() != 0 )
		return false;
	else
		return true;
}

bool CommandLine::hasArgument( const QString &arg ) const
{
	return( findOption( arg, Option::Argument ).type() == Option::Argument );
}

bool CommandLine::hasFlag( const QString &flag ) const
{
	return( findOption( flag, Option::Flag ).type() == Option::Flag );
}

QVariant CommandLine::argument( const QString &arg ) const
{
	return QVariant( findOption( arg, Option::Argument ).value() );
}

Option CommandLine::findOption( const QString &name, Option::Type type ) const
{
	foreach( Option option, m_options )
	{
		if( option.name() == name && option.type() == type )
			return option;
	}
	return Option();
}

Option::Type CommandLine::argumentType( const QString &arg ) const
{
	int index = 0;
	while( m_argDefs[index].name != 0 )
	{
		if( m_argDefs[index].name == arg )
			return m_argDefs[index].type;
		++index;
	}

	if( isNotSwitch( arg ) && !arg.isEmpty() )
		return Option::Other;
	else
		return Option::Invalid;
}

QString CommandLine::help( ) const
{
	int index = 0;
	QString argTemplate = "-%1=VALUE\t%2\t%3";
	QString flagTemplate = "-%1\t%2\t%3";
	QString returnString;
	QStringList argLines;
	QStringList flagLines;

	while( m_argDefs[index].name != 0 )
	{
		if( m_argDefs[index].type == Option::Argument )
		{
			if( m_argDefs[index].required )
				argLines << argTemplate.arg(m_argDefs[index].name)
							.arg( "*required")
							.arg( m_argDefs[index].description );
			else
				argLines << argTemplate.arg(m_argDefs[index].name)
							.arg( "")
							.arg( m_argDefs[index].description );
		}

		if( m_argDefs[index].type == Option::Flag )
		{
			if( m_argDefs[index].required )
				flagLines << flagTemplate.arg(m_argDefs[index].name)
							.arg( "*required")
							.arg( m_argDefs[index].description );
			else
				flagLines << flagTemplate.arg(m_argDefs[index].name)
							.arg( "")
							.arg( m_argDefs[index].description );
		}

		++index;
	}

	if( !argLines.isEmpty() )
		returnString += "Options:\n";
	returnString += argLines.join("\n");

	if( !flagLines.isEmpty() )
		returnString += "\nFlags:\n";
	returnString += flagLines.join("\n");

	return returnString + "\n";
}

QStringList CommandLine::files( ) const
{
	return m_files;
}
