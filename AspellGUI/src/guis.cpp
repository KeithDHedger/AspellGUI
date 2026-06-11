/*
 *
 * ©K. D. Hedger. 2015-2026 keithdhedger@gmail.com

 * This file (guis.cpp) is part of AspellGUI.

 * AspellGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * AspellGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with AspellGUI.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "globals.h"

void doAbout(void)
{
	AboutBoxClass	*about=new AboutBoxClass(window,QString("%1/pixmaps/AspellGUI.png").arg(realDataDir));
	QFile			file(QString("%1/docs/gpl-3.0.txt").arg(realDataDir));

	if(file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QTextStream in(&file);
			about->licence=in.readAll();
			file.close();
		}
	about->authors=credits;
	about->runAbout();
}

void buildMainGuiQt(void)
{
	QVBoxLayout	*vlayout=new QVBoxLayout;
	QWidget		*mainwidget=new QWidget;
	QWidget		*hbox;
	QHBoxLayout	*hlayout;
	QPushButton	*button;

	window=new QMainWindow;
	window->setWindowTitle("Aspell GUI");
	window->resize(420,150);

	bufferBox=new QPlainTextEdit(window);
	vlayout->setContentsMargins(0,0,0,0);
	vlayout->addWidget(bufferBox);
	hbox=new QWidget(window);
	hlayout=new QHBoxLayout(hbox);
	hbox->setLayout(hlayout);

//about
	button=new QPushButton("&About",window);
	button->setIcon(QIcon::fromTheme("help-about"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			doAbout();
		});
	hlayout->addWidget(button);

//spellcheck
	button=new QPushButton("&Spell Check",window);
	button->setIcon(QIcon::fromTheme("tools-check-spelling"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			doSpellCheckDoc();
		});
	hlayout->addWidget(button);

//check word
	button=new QPushButton("&Check Word",window);
	button->setIcon(QIcon::fromTheme("tools-check-spelling"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			checkWord();
		});
	hlayout->addWidget(button);
	
//quit
	button=new QPushButton("&Quit",window);
	button->setIcon(QIcon::fromTheme("application-exit"));
	hlayout->addWidget(button);
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			spellCheckWord->close();
			qApp->quit();
		});

//button box to main vbox
	vlayout->addWidget(hbox);
	mainwidget->setLayout(vlayout);
	window->setCentralWidget(mainwidget);
}

void buildWordCheckQt(int documentCheck)
{
	QVBoxLayout	*vlayout=new QVBoxLayout;
	QWidget		*hbox;
	QHBoxLayout	*hlayout;
	QPushButton	*button;

	spellCheckWord=new QDialog(window);

	hlayout=new QHBoxLayout;
	hbox=new QWidget(spellCheckWord);
	hbox->setLayout(hlayout);

	badWordLabel=new QLabel(QString("Change <i><b>%1</b></i> to: ").arg(badWord),spellCheckWord);
	hlayout->addWidget(badWordLabel);
	wordListDropbox=new QComboBox(spellCheckWord);
	hlayout->addWidget(wordListDropbox);
	vlayout->addWidget(hbox);

//buttons
	hlayout=new QHBoxLayout;
	hbox=new QWidget(spellCheckWord);
	hbox->setLayout(hlayout);

	button=new QPushButton("Apply",spellCheckWord);
	button->setIcon(QIcon::fromTheme("dialog-ok"));
	QObject::connect(button,&QPushButton::clicked,[documentCheck]()
		{
			doChangeWord(documentCheck);
		});
	hlayout->addWidget(button);

	button=new QPushButton("Ignore",spellCheckWord);
	button->setIcon(QIcon::fromTheme("list-remove"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			doAddIgnoreWord(1);
		});
	hlayout->addWidget(button);

	button=new QPushButton("Add",spellCheckWord);
	button->setIcon(QIcon::fromTheme("list-add"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			doAddIgnoreWord(2);
		});
	hlayout->addWidget(button);

	button=new QPushButton("Close",spellCheckWord);
	button->setIcon(QIcon::fromTheme("dialog-cancel"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			doCancelCheck();
		});
	hlayout->addWidget(button);

	vlayout->addWidget(hbox);
	spellCheckWord->setLayout(vlayout);
	spellCheckWord->setModal(true);
}
