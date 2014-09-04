/*
 *
 * K.D.Hedger 2013 <kdhedger68713@gmail.com>
 *
 * globals.cpp
 *
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
	#include <QObject>

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

