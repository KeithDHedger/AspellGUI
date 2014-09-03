/*
 *
 * K.D.Hedger 2013 <kdhedger68713@gmail.com>
 *
 * globals.h
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

#ifndef _GLOBALS_
#define _GLOBALS_

#define MYEMAIL "kdhedger68713@gmail.com"
#define MYWEBSITE "http://keithhedger.hostingsiteforfree.com"

#ifndef _USEQT5_

extern GtkWidget*		scrollBox;
extern GtkWidget*		textBox;
extern GtkWidget*		viewBox;
extern GtkWidget*		bufferBox;
extern GtkWidget*		window;
extern GtkWidget*		badWordLabel;

extern GtkWidget*		spellCheckWord;
extern GtkWidget*		wordListDropbox;
#endif

extern char*			badWord;
extern char*			goodWord;

extern AspellConfig*	aspellConfig;
extern AspellSpeller*	spellChecker;

extern int				numWords;

#endif




