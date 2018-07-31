/*
 *
 * ©K. D. Hedger. Thu 26 Nov 14:17:48 GMT 2015 keithdhedger@gmail.com

 * This file (globals.cpp) is part of AspellGUI.

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

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <aspell.h>

#include "config.h"

#ifndef _USEQT5_
	#include <gtk/gtk.h>
#else
	#include <glib.h>
	#include <QtWidgets>

	QApplication*	holdapp;
#endif

#include "globals.h"

Widget*			scrollBox=NULL;
Widget*			textBox=NULL;
Widget*			viewBox=NULL;
Widget*			bufferBox=NULL;
Widget*			window=NULL;
Widget*			badWordLabel=NULL;

Widget*			spellCheckWord=NULL;
Widget*			wordListDropbox;

//spellcheck
char*			badWord=NULL;
char*			goodWord=NULL;
AspellConfig*	aspellConfig;
AspellSpeller*	spellChecker=0;

int				numWords=0;

