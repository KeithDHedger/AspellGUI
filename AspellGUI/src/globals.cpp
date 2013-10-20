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
//#include "searchcallbacks.h"
//#include "callbacks.h"
//#include "script.h"

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

GtkNotebook*	notebook=NULL;
GtkWidget*		menubar=NULL;
GtkWidget*		menufile;
GtkWidget*		menuedit;
GtkWidget*		menuformat;
GtkWidget*		menuhelp;
GtkWidget*		menuprint;
GtkWidget*		menuclose;

GtkWidget*		redoMenu;
GtkWidget*		undoMenu;
GtkWidget*		saveMenu;
GtkWidget*		exportMenu;
GtkWidget*		exportAsMenu;
GtkWidget*		previewMenu;
GtkWidget*		saveAsMenu;
GtkWidget*		closeSectionMenu;


bool			gzipPages;
bool			lineWrap;
bool			highLight;
int				tabWidth;
char*			fontAndSize;
char*			terminalCommand;
bool			showLiveSearch;
bool			useUnderline;
bool			tmpGzipPages;
bool			tmpLineWrap;
bool			tmpHighLight;
int				tmpTabWidth;
bool			tmpShowLiveSearch;
bool			tmpUseUnderline;

int				windowWidth;
int				windowHeight;
int				windowX=-1;
int				windowY=-1;
bool			wrapSearch;
bool			insensitiveSearch;
bool			replaceAll;


//spellcheck
GtkWidget*		spellCheckWord;
GtkWidget*		wordListDropbox;
char*			badWord=NULL;
char*			goodWord=NULL;
AspellConfig*	aspellConfig;
AspellSpeller*	spellChecker=0;


