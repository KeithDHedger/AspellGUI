/*
 *
 * K.D.Hedger 2013 <kdhedger68713@gmail.com>
 *
*/

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "config.h"
#include "globals.h"
#include "spellcheck.h"

#ifndef _USEQT5_
	#include <gtk/gtk.h>
#else
	#include <glib.h>
	#include <QtWidgets>
	#include <QObject>
	#include "QT_button.h"
#endif

void doQtShutdown(QPushButton* data)
{
	qApp->quit();
}


void doShutdown(Widget* widget,gpointer data)
{
#ifndef _USEQT5_
	gtk_main_quit();
#endif
}

void doAbout(Widget* widget,gpointer data)
{
#ifndef _USEQT5_
	const char*	authors[]={"K.D.Hedger <"MYEMAIL">","\nMore by the same author\n","Xfce4-Composite-Editor\nhttp://gtk-apps.org/content/show.php/Xfce4-Composite-Editor?content=149523\n","KKEdit\nhttp://gtk-apps.org/content/show.php?content=158161\n","Manpage Editor\nhttp://gtk-apps.org/content/show.php?content=160219\n","GtkSu\nhttp://gtk-apps.org/content/show.php?content=158974",NULL};
	const char	copyright[] ="Copyright \xc2\xa9 2013 K.D.Hedger";
	char*		license=NULL;
	char*		doc=NULL;
	FILE*		fd=NULL;
	long		fsize=0;

	asprintf(&doc,"%s/docs/gpl-3.0.txt",DATADIR);
	fd=fopen(doc,"r");

	if(fd!=NULL)
		{
			fseek(fd,0,SEEK_END);
			fsize=ftell(fd);
			fseek(fd,0,SEEK_SET);
			license=(char*)malloc(fsize+1);
			fread(license,fsize,1,fd);
			fclose(fd);
			license[fsize]=0;
		}

	gtk_show_about_dialog(NULL,"authors",authors,"copyright",copyright,"version",VERSION,"website",MYWEBSITE,"program-name","Aspell GUI","logo-icon-name","AspellGUI","license",license,NULL); 
#endif
}

void doSticky(Widget* widget,gpointer data)
{
#ifndef _USEQT5_
	if(gtk_toggle_button_get_active((GtkToggleButton*)widget)==true)
		{
			gtk_window_stick(GTK_WINDOW(window));
			gtk_button_set_label((GtkButton*)widget,"Un-Stick");
			gtk_window_set_keep_above((GtkWindow*)window,true);
		}
	else
		{
			gtk_window_unstick(GTK_WINDOW(window));		
			gtk_button_set_label((GtkButton*)widget,"Stick");
			gtk_window_set_keep_above((GtkWindow*)window,false);
		}
#endif
}

#ifdef _USEQT5_

void buildMainGuiQt(void)
{
	QVBoxLayout*	vlayout=new QVBoxLayout;
	QWidget*		mainwidget=new QWidget;
	QWidget*		hbox;
	QHBoxLayout*	hlayout;
	Button*			button;

	window=new QMainWindow;
	window->setWindowTitle("Aspell GUI");
	window->setMinimumSize(320,60);
	
	bufferBox=new QTextEdit;
	vlayout->setContentsMargins(0,0,0,0);
	vlayout->addWidget(bufferBox);
	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

//about
	button=new Button("&About");
	hlayout->addWidget(button);
//spellcheck //doSpellCheckDoc
	button=new Button("&Spell Check");
	hlayout->addWidget(button);
	button->setCallBack((func_ptr)&doSpellCheckDoc);
//check word
	button=new Button("&Check Word");
	hlayout->addWidget(button);
//unstick
	button=new Button("&Un-Stick");
	hlayout->addWidget(button);
//quit
	button=new Button("&Quit");
	hlayout->addWidget(button);
	button->setCallBack((func_ptr)&doQtShutdown);

//button box to main vbox
	vlayout->addWidget(hbox);

	mainwidget->setLayout(vlayout);

	((QMainWindow*)window)->setCentralWidget(mainwidget);
}
#endif

#ifndef _USEQT5_
void buildMainGuiGtk(void)
{
	Widget*	vbox;
	Widget*	hbox;
	Widget*	button;
	Widget*	image;

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow*)window,"Aspell GUI");
	gtk_window_set_default_size((GtkWindow*)window,320,60);
	vbox=gtk_vbox_new(false,8);

//text to spell check
	scrollBox=gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	bufferBox=(Widget*)gtk_text_buffer_new(NULL);
	viewBox=(Widget*)gtk_text_view_new_with_buffer((GtkTextBuffer*)bufferBox);
	gtk_text_view_set_wrap_mode((GtkTextView*)viewBox,GTK_WRAP_WORD);
	gtk_container_add(GTK_CONTAINER(scrollBox),(Widget*)viewBox);
	gtk_container_add(GTK_CONTAINER(vbox),(Widget*)scrollBox);

//buttons
	hbox=gtk_hbox_new(false,8);

	button=gtk_button_new_from_stock(GTK_STOCK_ABOUT);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(doAbout),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,4);

	button=gtk_button_new_from_stock(GTK_STOCK_SPELL_CHECK);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doSpellCheckDoc),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);

	image=gtk_image_new_from_stock(GTK_STOCK_SPELL_CHECK,GTK_ICON_SIZE_MENU);
	button=gtk_button_new_with_label("Check Word");
	gtk_button_set_image((GtkButton*)button,image);

	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(checkWord),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);

	button=gtk_toggle_button_new_with_label("Un-Stick");
	gtk_toggle_button_set_active((GtkToggleButton*)button,true);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doSticky),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,true,true,2);

	button=gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doShutdown),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);
	gtk_container_add(GTK_CONTAINER(vbox),(Widget*)hbox);

	g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(doShutdown),NULL);
	gtk_container_add(GTK_CONTAINER(window),(Widget*)vbox);
}
#endif

#ifndef _USEQT5_
void buildWordCheckGtk(int documentCheck)
{
	Widget*	vbox;
	Widget*	button;
	Widget*	hbox;
	Widget*	image;
	char*		labeltext[512];
	int			docflag=documentCheck;

	spellCheckWord=gtk_dialog_new();
	gtk_window_set_title((GtkWindow*)spellCheckWord,"Spell check word");
	vbox=gtk_vbox_new(true,8);

	hbox=gtk_hbox_new(true,8);

	sprintf((char*)&labeltext,"Change <i><b>%s</b></i> to: ",badWord);
	badWordLabel=gtk_label_new((char*)&labeltext);
	gtk_label_set_use_markup((GtkLabel*)badWordLabel,true);
	gtk_box_pack_start(GTK_BOX(hbox),badWordLabel,true,true,0);

	wordListDropbox=gtk_combo_box_text_new();
	gtk_box_pack_start(GTK_BOX(hbox),wordListDropbox,true,true,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,true,true,0);

	hbox=gtk_hbox_new(true,8);
	button=gtk_button_new_from_stock(GTK_STOCK_APPLY);
	gtk_box_pack_start(GTK_BOX(hbox),button,true,true,0);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doChangeWord),(gpointer)(long)docflag);

	button=gtk_button_new_with_label("Ignore");
	image=gtk_image_new_from_stock(GTK_STOCK_ADD,GTK_ICON_SIZE_MENU);
	gtk_button_set_image((GtkButton*)button,image);
	gtk_box_pack_start(GTK_BOX(hbox),button,true,true,0);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doAddIgnoreWord),(gpointer)1);

	button=gtk_button_new_from_stock(GTK_STOCK_ADD);
	gtk_box_pack_start(GTK_BOX(hbox),button,true,true,0);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doAddIgnoreWord),(gpointer)2);

	button=gtk_button_new_from_stock(GTK_STOCK_CANCEL);
	gtk_box_pack_start(GTK_BOX(hbox),button,true,true,0);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doCancelCheck),NULL);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(),true,true,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,true,true,0);

	Widget* content=gtk_dialog_get_content_area((GtkDialog *)spellCheckWord);
	gtk_container_add(GTK_CONTAINER(content),(Widget*)vbox);

	gtk_signal_connect_object(GTK_OBJECT(spellCheckWord),"delete_event",GTK_SIGNAL_FUNC(gtk_widget_hide),GTK_OBJECT(spellCheckWord));
	gtk_signal_connect(GTK_OBJECT(spellCheckWord),"delete_event",GTK_SIGNAL_FUNC(gtk_true),NULL);
}
#else

void buildWordCheckQt(int documentCheck)
{
	QVBoxLayout*	vlayout=new QVBoxLayout;
	QWidget*		mainwidget=new QWidget;
	QWidget*		hbox;
	QHBoxLayout*	hlayout;
	Button*			button;

	char*			labeltext=NULL;
	int				docflag=documentCheck;
	QLabel*			label;

	spellCheckWord=new QMainWindow;
	spellCheckWord->setWindowTitle("Aspell GUI");
	spellCheckWord->setMinimumSize(320,60);
	
//	bufferBox=new QTextEdit;
//	vlayout->setContentsMargins(0,0,0,0);
//	vlayout->addWidget(bufferBox);
	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

//printf("AAA%sAAA\n",badWord);
	asprintf(&labeltext,"Change <i><b>%s</b></i> to: ",badWord);
	label=new QLabel(labeltext);
	hlayout->addWidget(label);
	wordListDropbox=new QComboBox;
	hlayout->addWidget(wordListDropbox);
	vlayout->addWidget(hbox);

//buttons
	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

	button=new Button("Apply");
	hlayout->addWidget(button);

	button=new Button("Ignore");
	hlayout->addWidget(button);

	button=new Button("Add");
	hlayout->addWidget(button);

	button=new Button("Cancel");
	hlayout->addWidget(button);

	vlayout->addWidget(hbox);

	mainwidget->setLayout(vlayout);
	((QMainWindow*)spellCheckWord)->setCentralWidget(mainwidget);
	spellCheckWord->show();
}
#endif
