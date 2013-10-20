/*
 *
 * K.D.Hedger 2013 <kdhedger68713@gmail.com>
 *
 * globals.cpp
 *
*/

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>

#include <aspell.h>
#include "globals.h"

GtkWidget*		nameBox;
GtkWidget*		sectionBox;
GtkWidget*		versionBox;
GtkWidget*		authorBox;
GtkWidget*		categoryBox;

GtkWidget*		scrollBox=NULL;
GtkWidget*		textBox=NULL;
GtkWidget*		viewBox=NULL;
GtkWidget*		bufferBox=NULL;
GtkWidget*		window=NULL;

//spellcheck
GtkWidget*		spellCheckWord;
GtkWidget*		wordListDropbox;
char*			badWord=NULL;
char*			goodWord=NULL;
AspellConfig*	aspellConfig;
AspellSpeller*	spellChecker=0;


