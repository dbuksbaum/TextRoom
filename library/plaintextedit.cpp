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
#include "plaintextedit.h"
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAbstractTextDocumentLayout>

PlainTextEdit::PlainTextEdit( QWidget *parent )
: QTextEdit(parent)
{
	setAcceptRichText(false);
}

void PlainTextEdit::focusOutEvent ( QFocusEvent * event )
{
    Q_UNUSED(event);
    emit editingFinished();
}

QSize PlainTextEdit::sizeHint( ) const
{
	QFontMetrics fm( font() );
	QSize size = QTextEdit::sizeHint();

	size.setHeight( fm.height() * 4 );

	return size;
}

QSize PlainTextEdit::minimumSizeHint( ) const
{
	QFontMetrics fm( font() );
	QSize size = QTextEdit::sizeHint();

	size.setHeight( fm.height() * 2 );

	return size;
}
