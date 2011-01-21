/***************************************************************************
*   Copyright (C) 2006-2008 by Ian Reinhart Geiser                        *
*   geiseri@yahoo.com                                                     *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/
#include "variantdompath.h"

#include <QBuffer>

VariantDomPath::VariantDomPath(const QDomElement& elem, const QString& path): DomPath(elem, path)
{}


VariantDomPath::VariantDomPath(const QDomDocument& doc, const QString& path): DomPath(doc, path)
{}


VariantDomPath::~VariantDomPath()
{}

void VariantDomPath::saveProperties( QHash< QString, QVariant > props )
{
	QString propertyNamePathTemplate = QLatin1String("properties/property[%2].name");
	QString propertyValuePathTemplate = QLatin1String("properties/property[%2]#text");
	QString propertyTypePathTemplate = QLatin1String("properties/property[%2].type");
	uint index = 0;

	foreach( QString propertyName, props.keys() )
	{
		QVariant property = props[propertyName];
		setValue( propertyNamePathTemplate.arg(index),
		                    propertyName );
		setValue( propertyTypePathTemplate.arg(index),
		                    QString::number( property.type() ) );
		if( property.canConvert(QVariant::String))
		{
			setValue( propertyValuePathTemplate.arg(index),
			                    property.toString() );
		}
		else
		{
			QBuffer buffer;
			buffer.open(QIODevice::WriteOnly);
			QDataStream ds(&buffer);
			ds << property;
			setValue( propertyValuePathTemplate.arg(index),
			                    buffer.data().toBase64() );
		}
		++index;
	}
}

QHash< QString, QVariant > VariantDomPath::loadProperties( )
{
	QHash<QString, QVariant> propertyMap;

	int propertyCount = count(QLatin1String("properties/property"));
	QString propertyNamePathTemplate = QLatin1String("properties/property[%1].name");
	QString propertyValuePathTemplate = QLatin1String("properties/property[%1]#text");
	QString propertyTypePathTemplate = QLatin1String("properties/property[%1].type");

	for(int idx = 0; idx < propertyCount; ++idx )
	{
		QString propertyName = getValue( propertyNamePathTemplate.arg(idx) );
		QString propertyValue = getValue( propertyValuePathTemplate.arg(idx) );
		int propertyType = getValue( propertyTypePathTemplate.arg(idx) ).toInt();

		QVariant property(propertyValue);

		if( !property.canConvert((QVariant::Type)propertyType) )
		{
			QByteArray encodedData = QByteArray::fromBase64(propertyValue.toLatin1());
			QBuffer buffer( &encodedData);
			buffer.open( QIODevice::ReadOnly );
			QDataStream ds(&buffer);
			ds >> property;
		}
		else
		{
			property.convert((QVariant::Type)propertyType);
		}
		propertyMap[propertyName] = property;
	}

	return propertyMap;
}



