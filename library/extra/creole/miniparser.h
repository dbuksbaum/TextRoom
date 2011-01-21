/***************************************************************************
 *   Copyright (C) 2007 by Ian Reinhart Geiser                             *
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
#ifndef STATE2_H
#define STATE2_H

#include <statemachinebase.h>

#include <QString>
#include <QList>

/**
	Handles the text format parsing.
	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class MiniParser : public StateMachineBase
{
public:
	MiniParser();

	~MiniParser();

	virtual void exec(Context* ctx);

	void turnOffTextFormats( Context* ctx );
private:
	bool m_newPara;
	bool m_inBold;
	bool m_inItalics;
	bool m_inUnderline;
	bool m_inCrossout;
};

#endif
