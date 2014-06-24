/*
 *
 * K.D.Hedger 2013 <kdhedger68713@gmail.com>
 *
 * globals.cpp
 *
*/

#include "globals.h"

GtkWidget*		scrollBox=NULL;
GtkWidget*		viewBox=NULL;
GtkWidget*		bufferBox=NULL;
GtkWidget*		window=NULL;
GtkWidget*		badWordLabel=NULL;

//spellcheck
GtkWidget*		spellCheckWord=NULL;
GtkWidget*		wordListDropbox;
char*			badWord=NULL;
char*			goodWord=NULL;
AspellConfig*	aspellConfig;
AspellSpeller*	spellChecker=NULL;

int				dictArraySize=0;
char**			dictArray=NULL;

int				numWords=0;

