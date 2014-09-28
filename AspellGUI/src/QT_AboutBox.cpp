/******************************************************
*
*     ©keithhedger Wed 24 Sep 15:54:11 BST 2014
*     kdhedger68713@gmail.com
*
*     QT_AboutBox.cpp
* 
******************************************************/
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QtWidgets>
#include "QT_button.h"
#include "QT_AboutBox.h"
#include <QPushButton>
#include <QtWidgets>

void AboutBoxClass::setAuthors(char* authors)
{
	this->authors=strdup(authors);
}

void AboutBoxClass::runAbout(void)
{
	this->aboutdialog->exec();
}

void AboutBoxClass::setLicence(char* licence)
{
	this->licence=strdup(licence);
}

AboutBoxClass::~AboutBoxClass()
{
	free(this->licence);
	free(this->authors);
}

void AboutBoxClass::killCreditsBox(void)
{
	this->creditsdialog->close();
}

void AboutBoxClass::showCredits(void)
{
	QPushButton*	button;
	QHBoxLayout*	hlayout;
	QWidget*		hbox;
	QVBoxLayout*	vlayout=new QVBoxLayout;
	QTabWidget*		tabWidget=new QTabWidget;

	this->creditsdialog=new QDialog(this->aboutdialog);
	this->creditsdialog->setWindowTitle("Credits");
	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

	QTextBrowser*	text=new QTextBrowser;
	text->setText(this->authors);
	text->setReadOnly(true);
	text->setOpenExternalLinks(true);

	tabWidget->addTab(text,"Written By");
	vlayout->addWidget(tabWidget);

//close
	hlayout->setContentsMargins(0,0,0,0);
	button=new QPushButton("&Close");
	connect(button,SIGNAL(clicked()),this,SLOT(killCreditsBox()));
	hlayout->addWidget(button);

	button->setIcon(QIcon::fromTheme("window-close"));
	hlayout->insertStretch(0,1);
	vlayout->addWidget(hbox);

	creditsdialog->setLayout((QLayout*)vlayout);
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
	QPushButton*	button;
	QHBoxLayout*	hlayout;
	QWidget*		hbox;
	QVBoxLayout*	vlayout=new QVBoxLayout;
	QPlainTextEdit*	text=new QPlainTextEdit;

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
	connect(button,SIGNAL(clicked()),this,SLOT(killLicenceBox()));
	button->setIcon(QIcon::fromTheme("window-close"));
	hlayout->addWidget(button);

	hlayout->insertStretch(0,1);
	vlayout->addWidget(hbox);

	this->licencedialog->setLayout((QLayout*)vlayout);
	this->licencedialog->setModal(true);
	this->licencedialog->resize(500,320);
	this->licencedialog->exec();

	delete text;
	delete button;
	delete hlayout;
	delete vlayout;
	delete this->licencedialog;
}

AboutBoxClass::AboutBoxClass(QWidget* window,char* pixpath)
{
	QVBoxLayout*	vlayout=new QVBoxLayout;
	QWidget*		hbox;
	QHBoxLayout*	hlayout;
	QPushButton*	button;

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
	label->setText("<font size=\"5\"><b>About Box</b></font>");
	label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	vlayout->addWidget(label);
//text
	label=new QLabel;
	label->setText("My About Box");
	label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	vlayout->addWidget(label);
//copyrite
	label=new QLabel;
	label->setText("<small>Copyright \xc2\xa9 2013-2014 K.D.Hedger</small>");
	label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	vlayout->addWidget(label);
//homepage
	label=new QLabel;
	label->setText("<a href=\"https://sites.google.com/site/kkeditlinuxtexteditor/home\">https://sites.google.com/site/kkeditlinuxtexteditor/home</a>");
	//label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
	label->setOpenExternalLinks(true);
	label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	vlayout->addWidget(label);
//credits
	button=new QPushButton("&Credits");
	connect(button,SIGNAL(clicked()),this,SLOT(showCredits()));
	hlayout->addWidget(button);
	button->setIcon(QIcon::fromTheme("help-about"));

//licence
	button=new QPushButton("&Licence");
	connect(button,SIGNAL(clicked()),this,SLOT(showLicence()));
	hlayout->addWidget(button);

//close
	button=new QPushButton("&Close");
	connect(button,SIGNAL(clicked()),this,SLOT(killAboutBox()));
	hlayout->addWidget(button);
	button->setIcon(QIcon::fromTheme("window-close"));

	vlayout->addWidget(hbox);
	this->aboutdialog->setLayout((QLayout*)vlayout);
}


