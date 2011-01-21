/****************************************************************************
** Copyright (C) 2008 Petar Toushkov <peter dot toushkov at gmail.com>
** Copyright (C) 2008 Omer Bahri Gordebak <gordebak at gmail.com>
**
** Additional help, code and insights by:
** adamvert - from http://ubuntuforums.org/
** zebulon M - from http://ubuntuforums.org/
**
** Artwork by Edward Solodukhin <arch1000@gmail.com>
**
** Parts of the following code are from the Phrasis project:
**
** http://code.google.com/p/phrasis/
**
** and are
**
** Copyright (C) 2006 Jacob R Rideout <jacob@jacobrideout.net>
** All rights reserved.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/


#include "musicroom.h"
#include <SDL/SDL.h>
#ifdef Q_OS_MACX
# include <SDL_mixer/SDL_mixer.h>
#else
# include <SDL/SDL_mixer.h>
#endif
#include <QtGui>
#include <QWidget>
#include "textroom.h"

MusicRoom::MusicRoom(QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	readSong();

  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16SYS;
  int audio_channels = 2;
  int audio_buffers = 4096;
  SDL_Init(SDL_INIT_AUDIO);

  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Unable to open audio!\n");
    exit(1);
  }
  Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
  Mix_CloseAudio();
  SDL_Quit();
}

void MusicRoom::on_actionLoad_activated()
{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath() );
		songPath = fileName;
}

void MusicRoom::on_actionPlay_activated()
{
	music=Mix_LoadMUS(songPath.toUtf8());
	if(!music) {
	    printf("Mix_LoadMUS("+songPath.toUtf8()+"): %s\n", Mix_GetError());
	}
	if(Mix_PlayMusic(music, 0)==-1) {
	    printf("Mix_PlayMusic: %s\n", Mix_GetError());
 	}
}

void MusicRoom::hideEvent(QHideEvent * event)
{
	writeSong();
	Mix_FreeMusic(music);
	music=NULL;
	done(1);
	accept();
}

void MusicRoom::readSong()
{
#ifdef Q_OS_WIN32
	QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName());
#else
	QSettings settings;
#endif
	songPath = settings.value("Song", "").toString();
}

void MusicRoom::writeSong()
{
#ifdef Q_OS_WIN32
	QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName());
#else
	QSettings settings;
#endif
	settings.setValue("Song", songPath);
}
