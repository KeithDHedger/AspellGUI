/******************************************************
*
*     ©keithhedger Wed 24 Sep 15:54:11 BST 2014
*     kdhedger68713@gmail.com
*
*     QT_AboutBox.h
* 
******************************************************/

#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QtWidgets>
#include "QT_button.h"

#ifndef _QT_ABOUTBOX_
#define _QT_ABOUTBOX_

#define MYEMAIL "kdhedger68713@gmail.com"

class AboutBoxClass : public QObject
{
    Q_OBJECT

	public:
		AboutBoxClass(QWidget* window,char* pixpath);
		~AboutBoxClass();

		void runAbout(void);
		void setLicence(char* licence);
		void setAuthors(char* authors);

	private slots:
		void showLicence(void);
		void showCredits(void);
		void killLicenceBox(void);
		void killAboutBox(void);
		void killCreditsBox(void);

	private:
		QDialog*	aboutdialog;
		QDialog*	licencedialog;
		QDialog*	creditsdialog;
		char*		licence;
		char*		authors;
};

#endif
