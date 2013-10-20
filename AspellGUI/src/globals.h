/*
 *
 * K.D.Hedger 2013 <kdhedger68713@gmail.com>
 *
 * globals.h
 *
*/
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include <aspell.h>

#include "config.h"

#ifndef _GLOBALS_
#define _GLOBALS_

#define MYEMAIL "kdhedger68713@gmail.com"
#define MYWEBSITE "http://keithhedger.hostingsiteforfree.com"

extern GtkWidget*		nameBox;
extern GtkWidget*		sectionBox;
extern GtkWidget*		versionBox;
extern GtkWidget*		authorBox;
extern GtkWidget*		categoryBox;

extern GtkWidget*		scrollBox;
extern GtkWidget*		textBox;
extern GtkWidget*		viewBox;
extern GtkWidget*		bufferBox;
extern GtkWidget*		window;
extern GtkWidget*		badWordLabel;

extern GtkWidget*		spellCheckWord;
extern GtkWidget*		wordListDropbox;
extern char*			badWord;
extern char*			goodWord;

extern AspellConfig*	aspellConfig;
extern AspellSpeller*	spellChecker;

extern int				numWords;

#endif




