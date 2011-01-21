#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QTextEdit>
class QAction;
class QContextMenuEvent;

class PlainTextEdit : public QTextEdit
{
Q_OBJECT
Q_PROPERTY( QString text READ toPlainText WRITE setPlainText  )
public:
	PlainTextEdit( QWidget *parent = 0 );

	virtual QSize sizeHint () const;
	virtual QSize minimumSizeHint () const;

protected:
	void focusOutEvent ( QFocusEvent * event );

signals:
	void editingFinished();
};

#endif
