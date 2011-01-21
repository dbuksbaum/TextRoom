#include <QApplication>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QTextEdit>
#include <QTextCursor>

#include "wikilexer.h"
#include "statemachinebase.h"
#include "parser.h"
#include "xhtmlobserver.h"
#include "qtextdocumentparserobserver.h"

int main ( int argc, char** argv )
{
	QApplication app(argc, argv );
	QFile wiki ( "../tests/input.wiki" );
	QFile html ( "output.html" );

	if ( wiki.open ( QIODevice::ReadOnly ) && html.open ( QIODevice::WriteOnly ) )
	{
		StateMachineBase::Context ctx;
		QXmlStreamWriter qout ( &html );
		qout.setAutoFormatting(true);
		qout.writeStartDocument();
		qout.writeStartElement("html");
		qout.writeStartElement("head");
		qout.writeEndElement();
		qout.writeStartElement("body");

		ctx.lexer = new WikiLexer;
		ctx.observer = new XHTMLObserver ( "", &qout );
		ctx.nextState = new Parser;

		ctx.lexer->setInput ( QString::fromUtf8( wiki.readAll() ) );
		ctx.observer->startPage( "Test Wiki" );
		while ( ctx.nextState != 0 )
			ctx.nextState->exec ( &ctx );
		ctx.observer->endPage();
		qout.writeEndDocument();
		html.close();
		QDesktopServices::openUrl ( html.fileName() );
		wiki.close();
	}
}
