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

/*
#define REPLACE			100
#define FINDNEXT		200
#define FINDPREV		300
*/
#define MYEMAIL "kdhedger68713@gmail.com"
#define MYWEBSITE "http://keithhedger.hostingsiteforfree.com"

/*
#define VALIDCHARS "[]a-zA-Z0-9:/@ ()_-,.*#;[\"]"
#define VALIDFILENAMECHARS "[A-Za-z0-9_-./ ]"
#define VALIDFUNCTIONCHARS "[A-Za-z0-9_*]"

#define BOLDESC "\e[1m"
#define ITALICESC "\e[4m"
#define ITALIC1ESC "\e[22m"
#define ITALIC2ESC "\e[24m"

#define NORMALESC "\e[0m"
#define NORMALESC1 "\e[4m"
#define NORMALESC2 "\e[24m"
#define NORMALESC3 "\e[22m"
*/

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

/*
extern GtkNotebook*		notebook;

extern GtkWidget*		menubar;
extern GtkWidget*		menufile;
extern GtkWidget*		menuedit;
extern GtkWidget*		menuformat;
extern GtkWidget*		menuhelp;
extern GtkWidget*		menuprint;
extern GtkWidget*		menuclose;

extern GtkWidget*		redoMenu;
extern GtkWidget*		undoMenu;
extern GtkWidget*		saveMenu;
extern GtkWidget*		exportMenu;
extern GtkWidget*		exportAsMenu;
extern GtkWidget*		previewMenu;
extern GtkWidget*		saveAsMenu;
extern GtkWidget*		closeSectionMenu;

extern GtkWidget*		liveSearchWidget;
extern int				currentPage;

extern GtkWidget*		prefswin;
extern GtkWidget*		terminalBox;

extern bool				gzipPages;
extern bool				lineWrap;
extern bool				highLight;
extern int				tabWidth;
extern char*			fontAndSize;
extern char*			terminalCommand;
extern bool				showLiveSearch;
extern bool				useUnderline;
extern GtkWidget*		fontBox;
extern bool				tmpGzipPages;
extern bool				tmpLineWrap;
extern bool				tmpHighLight;
extern int				tmpTabWidth;
extern bool				tmpShowLiveSearch;
extern bool				tmpUseUnderline;

extern int				windowWidth;
extern int				windowHeight;
extern int				windowX;
extern int				windowY;
extern bool				wrapSearch;
extern bool				insensitiveSearch;
extern bool				replaceAll;

extern int				currentTabNumber;

*/

extern GtkWidget*		spellCheckWord;
extern GtkWidget*		wordListDropbox;
extern char*			badWord;
extern char*			goodWord;

extern AspellConfig*	aspellConfig;
extern AspellSpeller*	spellChecker;


#endif




