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
	AboutBoxClass	about(window,QString("%1/pixmaps/AspellGUI.png").arg(realDataDir));
	QFile			file(QString("%1/docs/gpl-3.0.txt").arg(realDataDir));

	if(file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QTextStream in(&file);
			about.licence=in.readAll();
			file.close();
		}
	about.credits=credits;
	about.setHomepage(GLOBALWEBSITE,"Home Page");
	about.setBodyText("A simple GUI for aspell.");
	about.runAbout();
}

void buildMainGuiQt(void)
{
	QVBoxLayout					*vlayout=new QVBoxLayout;
	QWidget						*mainwidget=new QWidget;
	QWidget						*hbox;
	QHBoxLayout					*hlayout;
	QPushButton					*button;
	QStringList					ll;
	const char					*data;

	window=new QMainWindow;
	globalChecker=new QT_SpellCheckClass(window);

	window->setWindowTitle("Aspell GUI");
	window->resize(420,150);

	bufferBox=new QPlainTextEdit(window);
	vlayout->setContentsMargins(0,0,0,0);
	vlayout->addWidget(bufferBox);
	hbox=new QWidget(window);
	hlayout=new QHBoxLayout(hbox);
	hbox->setLayout(hlayout);

	globalChecker->te=bufferBox;

//about
	button=new QPushButton("&About",window);
	button->setIcon(QIcon::fromTheme("help-about"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			doAbout();
		});
	hlayout->addWidget(button);

	ll=globalChecker->getLanguageCodes();
	ll.removeDuplicates();
	langCode=new QComboBox(window);
	langCode->addItems(ll);
	data=aspell_config_retrieve(globalChecker->getConfig(),"lang");
	langCode->setCurrentIndex(langCode->findText(data));
	QObject::connect(langCode,&QComboBox::currentIndexChanged,[](int index)
		{
			globalChecker->setLanguage(langCode->currentText());
			qDebug()<<"Language:"<<langCode->currentText();
		});
  	hlayout->addWidget(langCode);

//spellcheck
	button=new QPushButton("Check &Text",window);
	button->setIcon(QIcon::fromTheme("tools-check-spelling"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			globalChecker->doSpellCheckDoc();
		});
	hlayout->addWidget(button);

//check word
	button=new QPushButton("Check &Word",window);
	button->setIcon(QIcon::fromTheme("tools-check-spelling"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			globalChecker->doSpellCheckWord(bufferBox->textCursor().selectedText());
		});
	hlayout->addWidget(button);
	
//quit
	button=new QPushButton("&Quit",window);
	button->setIcon(QIcon::fromTheme("application-exit"));
	hlayout->addWidget(button);
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			qApp->quit();
		});

//button box to main vbox
	vlayout->addWidget(hbox);
	mainwidget->setLayout(vlayout);
	window->setCentralWidget(mainwidget);
}
