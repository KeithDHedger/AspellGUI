/******************************************************
*
*     ©keithhedger Tue 16 Jul 20:46:19 BST 2013
*     kdhedger68713@gmail.com
*
*     spellcheck.h
* 
******************************************************/
#ifndef _USEQT5_
	#include <gtk/gtk.h>
#else
	#include <glib.h>
	#include <QtWidgets>
	#include <QObject>
#endif

#include "config.h"

#ifndef _SPELLCHECK_
#define _SPELLCHECK_

#ifndef _USEQT5_
void checkWord(Widget* widget,gpointer data);
#else
void checkWord(QPushButton* data);
#endif


#ifndef _USEQT5_
void doChangeWord(Widget* widget,gpointer data);
#else
void doChangeWord(Widget* widget);
#endif

void doAddIgnoreWord(Widget* widget,gpointer data);

#ifndef _USEQT5_
void doSpellCheckDoc(Widget* widget,gpointer data);
#else
void doSpellCheckDoc(QPushButton* data);
#endif

void doCancelCheck(Widget* widget,gpointer data);

#endif
