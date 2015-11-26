/*
 *
 * ©K. D. Hedger. Thu 26 Nov 14:18:03 GMT 2015 kdhedger68713@gmail.com

 * This file (globals.h) is part of AspellGUI.

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

#ifndef _GLOBALS_
#define _GLOBALS_

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <aspell.h>

#include "config.h"

#ifndef _USEQT5_
	#include <gtk/gtk.h>
	typedef GtkWidget Widget;
#else
	#include <glib.h>
	#include <QtWidgets>
	typedef QWidget Widget;

	extern QApplication*	holdapp;
#endif

#define MYEMAIL "keithhedger@keithhedger.darktech.org"
#define MYWEBSITE "http://khapplications.darktech.org/pages/aspellgui/aspelgui.html"
#define GLOBALWEBSITE "http://khapplications.darktech.org/index.html"
#define	QTMAPPICON DATADIR "/pixmaps/AspellGUI48.png"

extern Widget*				scrollBox;
extern Widget*				textBox;
extern Widget*				viewBox;
extern Widget*				bufferBox;
extern Widget*				window;
extern Widget*				badWordLabel;

extern Widget*				spellCheckWord;
extern Widget*				wordListDropbox;
#endif

extern char*				badWord;
extern char*				goodWord;

extern AspellConfig*		aspellConfig;
extern AspellSpeller*		spellChecker;

extern int					numWords;

