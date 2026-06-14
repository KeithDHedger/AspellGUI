/*
 *
 * ©K. D. Hedger. 2015-2026 keithdhedger@gmail.com

 * This file (QT_AboutBox.cpp) is part of AspellGUI.

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

#include "QT_AboutBox.h"

void AboutBoxClass::runAbout(void)
{
	this->aboutdialog->exec();
}

AboutBoxClass::~AboutBoxClass()
{
}

void AboutBoxClass::killCreditsBox(void)
{
	this->creditsdialog->close();
}

void AboutBoxClass::showCredits(void)
{
	QPushButton	*button;
	QHBoxLayout	*hlayout;
	QWidget		*hbox;
	QVBoxLayout	*vlayout=new QVBoxLayout;
	QTabWidget	*tabWidget=new QTabWidget;

	this->creditsdialog=new QDialog(this->aboutdialog);
	this->creditsdialog->setWindowTitle("Credits");
	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

	QTextBrowser	*text=new QTextBrowser;
	text->setHtml(this->authors);
	text->setReadOnly(true);
	text->setOpenExternalLinks(true);

	tabWidget->addTab(text,"Written By");
	vlayout->addWidget(tabWidget);

//close
	hlayout->setContentsMargins(0,0,0,0);
	button=new QPushButton("&Close");
	QObject::connect(button,&QPushButton::clicked,[this]()
		{
			this->killCreditsBox();
		});
	hlayout->addWidget(button);

	button->setIcon(QIcon::fromTheme("window-close"));
	hlayout->insertStretch(0,1);
	vlayout->addWidget(hbox);

	creditsdialog->setLayout(vlayout);
	creditsdialog->setModal(true);
	creditsdialog->resize(500,320);
	creditsdialog->exec();

	delete text;
	delete button;
	delete hlayout;
	delete vlayout;
	delete this->creditsdialog;
}

void AboutBoxClass::killLicenceBox(void)
{
	this->licencedialog->close();
}

void AboutBoxClass::killAboutBox(void)
{
	this->aboutdialog->close();
	delete this;
}

void AboutBoxClass::showLicence(void)
{
	QPushButton		*button;
	QHBoxLayout		*hlayout;
	QWidget*			hbox;
	QVBoxLayout		*vlayout=new QVBoxLayout;
	QPlainTextEdit	*text=new QPlainTextEdit;

	this->licencedialog=new QDialog(this->aboutdialog);
	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

	this->licencedialog->setWindowTitle("Licence");
	vlayout->setContentsMargins(0,4,4,4);
	text->setPlainText(this->licence);
	text->setReadOnly(true);
	text->setLineWrapMode(QPlainTextEdit::NoWrap);
	vlayout->addWidget(text);

//close
	hlayout->setContentsMargins(0,0,0,0);
	button=new QPushButton("&Close");
	button->setIcon(QIcon::fromTheme("window-close"));
	QObject::connect(button,&QPushButton::clicked,[this]()
		{
			this->killLicenceBox();
		});
	hlayout->addWidget(button);

	hlayout->insertStretch(0,1);
	vlayout->addWidget(hbox);

	this->licencedialog->setLayout(vlayout);
	this->licencedialog->setModal(true);
	this->licencedialog->resize(500,320);
	this->licencedialog->exec();

	delete text;
	delete button;
	delete hlayout;
	delete vlayout;
	delete this->licencedialog;
}

AboutBoxClass::AboutBoxClass(QWidget *window,QString pixpath)
{
	QVBoxLayout	*vlayout=new QVBoxLayout;
	QWidget		*hbox;
	QHBoxLayout	*hlayout;
	QPushButton	*button;

	QPixmap		pic(pixpath);
	QLabel*		label=new QLabel;

	this->aboutdialog=new QDialog(window);
	this->aboutdialog->setWindowTitle("About");
	this->aboutdialog->resize(320,128);
	this->aboutdialog->setModal(true);

	vlayout->setContentsMargins(0,4,0,0);
	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

//icon
	label->setPixmap(pic);
	label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	vlayout->addWidget(label);
//progname
	label=new QLabel;
	label->setText("<font size=\"5\"><b>" PACKAGE_STRING "</b></font>");
	label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	vlayout->addWidget(label);
//text
	label=new QLabel;
	label->setText("A Simple GUI for aspell");
	label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	vlayout->addWidget(label);
//copyrite
	label=new QLabel;
	label->setText("<small>" COPYRITE "</small>");
	label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	vlayout->addWidget(label);
//homepage
	label=new QLabel;
	label->setText("<a href=\"" ASPELLPAGE "\">Aspell GUI Page</a>");
	label->setOpenExternalLinks(true);
	label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	vlayout->addWidget(label);
//credits
	button=new QPushButton("&Credits");
	button->setIcon(QIcon::fromTheme("help-about"));
	QObject::connect(button,&QPushButton::clicked,[this]()
		{
			this->showCredits();
		});
	hlayout->addWidget(button);

//licence
	button=new QPushButton("&Licence");
	button->setIcon(QIcon::fromTheme("text-x-license"));
	QObject::connect(button,&QPushButton::clicked,[this]()
		{
			this->showLicence();
		});
	hlayout->addWidget(button);

//about qt
	button=new QPushButton("&About Qt");
	button->setIcon(QIcon::fromTheme("help-about"));
	QObject::connect(button,&QPushButton::clicked,[this]()
		{
			qApp->aboutQt();
		});
	hlayout->addWidget(button);

//close
	button=new QPushButton("&Close");
	button->setIcon(QIcon::fromTheme("window-close"));
	QObject::connect(button,&QPushButton::clicked,[this]()
		{
			this->killAboutBox();
		});
	hlayout->addWidget(button);

	vlayout->addWidget(hbox);
	this->aboutdialog->setLayout(vlayout);
}


