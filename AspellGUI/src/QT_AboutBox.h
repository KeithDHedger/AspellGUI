/*
 *
 * ©K. D. Hedger. Thu 26 Nov 14:19:15 GMT 2015 keithdhedger@gmail.com

 * This file (QT_AboutBox.h) is part of AspellGUI.

 * AspellGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * AspellGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with AspellGUI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "globals.h"

#ifndef _QT_ABOUTBOX_
#define _QT_ABOUTBOX_

class AboutBoxClass : public QObject
{

	public:
		AboutBoxClass(QWidget *window,const char *pixpath);
		~AboutBoxClass();

		QString	licence;
		QString	authors;

		void		runAbout(void);

	private:
		QDialog	*aboutdialog;
		QDialog	*licencedialog;
		QDialog	*creditsdialog;

		void		showLicence(void);
		void		showCredits(void);
		void		killLicenceBox(void);
		void		killAboutBox(void);
		void		killCreditsBox(void);
};

#endif
