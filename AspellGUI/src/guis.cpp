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
	about->credits=credits;
	about->setHomepage(GLOBALWEBSITE,"Home Page");
	about->setBodyText("A simple GUI for aspell.");
	about->runAbout();
}

void setLanguage(QString lang)
{
	aspell_config_replace(aspellConfig,"lang",qPrintable(langCode->currentText()));
	possible_err=new_aspell_speller(aspellConfig);
	if(spellChecker!=NULL)
		delete_aspell_speller(spellChecker);
	spellChecker=NULL;

	if(aspell_error_number(possible_err)!= 0)
		puts(aspell_error_message(possible_err));
	else
		spellChecker=to_aspell_speller(possible_err);
}

void buildMainGuiQt(void)
{
	QVBoxLayout					*vlayout=new QVBoxLayout;
	QWidget						*mainwidget=new QWidget;
	QWidget						*hbox;
	QHBoxLayout					*hlayout;
	QPushButton					*button;
	QStringList					ll;

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

//lang code
	AspellDictInfoList			*dlist;
	AspellDictInfoEnumeration	*dels;
	const AspellDictInfo			*entry;

	dlist=get_aspell_dict_info_list(aspellConfig);
	dels=aspell_dict_info_list_elements(dlist);

	while((entry=aspell_dict_info_enumeration_next(dels))!=0) 
		ll<<entry->code;
	ll.removeDuplicates();
	langCode=new QComboBox(window);
	langCode->addItems(ll);
	QObject::connect(langCode,&QComboBox::currentIndexChanged,[](int index)
		{
			setLanguage(langCode->currentText());
		});

	delete_aspell_dict_info_enumeration(dels);
  	hlayout->addWidget(langCode);

//spellcheck
	button=new QPushButton("Check &Text",window);
	button->setIcon(QIcon::fromTheme("tools-check-spelling"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
		spellCheckWord->done(0);
			delete spellCheckWord;
			spellCheckWord=NULL;
			buildWordCheckQt(1);
			doSpellCheckDoc();
		});
	hlayout->addWidget(button);

//check word
	button=new QPushButton("Check &Word",window);
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
	QSettings	prefs("KDHedger","AspellGUI");

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

	button=new QPushButton("&Apply",spellCheckWord);
	button->setIcon(QIcon::fromTheme("dialog-ok"));
	QObject::connect(button,&QPushButton::clicked,[documentCheck]()
		{
			doChangeWord(documentCheck);
		});
	hlayout->addWidget(button);

	button=new QPushButton("&Ignore",spellCheckWord);
	button->setIcon(QIcon::fromTheme("list-remove"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			doAddIgnoreWord(1);
		});
	hlayout->addWidget(button);

	button=new QPushButton("A&dd",spellCheckWord);
	button->setIcon(QIcon::fromTheme("list-add"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			doAddIgnoreWord(2);
		});
	hlayout->addWidget(button);

	button=new QPushButton("&Close",spellCheckWord);
	button->setIcon(QIcon::fromTheme("dialog-cancel"));
	QObject::connect(button,&QPushButton::clicked,[]()
		{
			doCancelCheck();
		});
	hlayout->addWidget(button);

	vlayout->addWidget(hbox);
	spellCheckWord->setLayout(vlayout);
	spellCheckWord->setModal(true);
	spellCheckWord->restoreGeometry(prefs.value("wordgeom").toByteArray());
}
