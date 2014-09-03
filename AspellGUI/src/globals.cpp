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
#endif

#include "globals.h"

#ifndef _USEQT5_
	GtkWidget*		scrollBox=NULL;
	GtkWidget*		textBox=NULL;
	GtkWidget*		viewBox=NULL;
	GtkWidget*		bufferBox=NULL;
	GtkWidget*		window=NULL;
	GtkWidget*		badWordLabel=NULL;

	GtkWidget*		spellCheckWord=NULL;
	GtkWidget*		wordListDropbox;
#endif

//spellcheck
char*			badWord=NULL;
char*			goodWord=NULL;
AspellConfig*	aspellConfig;
AspellSpeller*	spellChecker=0;

int				numWords=0;

