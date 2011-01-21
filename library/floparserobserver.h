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
#ifndef FLOPARSEROBSERVER_H
#define FLOPARSEROBSERVER_H

#include <parserobserverbase.h>
class MindMap;
class Block;

/**
An observer that will generate a Flo document from a wiki page.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class FloParserObserver : public ParserObserverBase
{
public:
    FloParserObserver(MindMap *mindMap, const QString& baseAnchorUrl);

    ~FloParserObserver();

    virtual void addText(const QString& text);
    virtual void drawAnchor(const QString& url, const QString& title);
    virtual void drawHeading(int level, const QString& text);
    virtual void drawHrule(); /// ignore
    virtual void drawImage(const QString& url, const QString& title);
    virtual void drawLineBreak(); /// ignore
    virtual void endBold(); /// ignore
    virtual void endCrossout(); /// ignore
    virtual void endItalics(); /// ignore
    virtual void endListItem();
    virtual void endOrderedList();
    virtual void endPage();
    virtual void endParagraph();
    virtual void endPreformatted(); /// ignore
    virtual void endTable(); /// ignore
    virtual void endTableCell(); /// ignore
    virtual void endTableHeaderCell(); /// ignore
    virtual void endTableRow(); /// ignore
    virtual void endTypewriter(); /// ignore
    virtual void endUnderline(); /// ignore
    virtual void endUnOrderedList();
    virtual void startBold(); /// ignore
    virtual void startCrossout(); /// ignore
    virtual void startItalics(); /// ignore
    virtual void startListItem();
    virtual void startOrderedList();
    virtual void startPage(const QString& title);
    virtual void startParagraph();
    virtual void startPreformatted(); /// ignore
    virtual void startTable(); /// ignore
    virtual void startTableCell(); /// ignore
    virtual void startTableHeaderCell(); /// ignore
    virtual void startTableRow(); /// ignore
    virtual void startTypewriter(); /// ignore
    virtual void startUnderline(); /// ignore
    virtual void startUnOrderedList();
private:
    MindMap *m_map;
    Block *m_currentBlock;
};

#endif
