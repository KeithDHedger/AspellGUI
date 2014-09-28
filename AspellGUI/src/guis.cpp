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
	#include "QT_button.h"
	#include "QT_AboutBox.h"

const char*	authors="K.D.Hedger ©2013-2014<br><a href=\"mailto:" MYEMAIL "\">Email Me</a><br>" \
				"<a href=\"https://sites.google.com/site/kkeditlinuxtexteditor/home\">Homepage</a>" \
				"<br><br>More by the same author<br>" \
				"<a href=\"http://xfce-look.org/content/show.php/Xfce-Theme-Manager?content=149647\">Xfce-Theme-Manager<br>" \
				"<a href=\"http://gtk-apps.org/content/show.php/Xfce4-Composite-Editor?content=149523\">Xfce4-Composite-Editor</a><br>" \
				"<a href=\"http://gtk-apps.org/content/show.php?content=158161\">KKEdit</a><br>" \
				"<a href=\"http://gtk-apps.org/content/show.php?content=160219\">Manpage Editor</a><br>" \
				"<a href=\"http://gtk-apps.org/content/show.php?content=158974\">GtkSu<br>" \
				"<a href=\"http://gtk-apps.org/content/show.php?content=161353\">ASpell GUI<br>" \
				"<a href=\"http://gtk-apps.org/content/show.php/Clipboard+Viewer?content=121667\">Clipboard Viewer<br>";

#endif

void doShutdown(Widget* widget,gpointer data)
{
#ifndef _USEQT5_
	gtk_main_quit();
#else
	qApp->quit();
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
#else

//	QMessageBox*	msgBox=new QMessageBox;
//	Qt::WindowFlags flags;
//
//	msgBox->setText("<pre>                               </pre><font size="5"><b>AspellGUI " VERSION "</b></font>");
//	msgBox->setInformativeText("Copyright xc2xa9 2013-2014 K.D.Hedger<br><nobr><a href="" MYWEBSITE "">" MYWEBSITE "</a></nobr>");
//	msgBox->addButton("&Close", QMessageBox::AcceptRole);
//	msgBox->setIconPixmap(QPixmap(QTMAPPICON));
//
//	flags=msgBox->windowFlags();
//	msgBox->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
//
//	msgBox->setModal(true);
//	msgBox->exec();

	char*			licence=NULL;
	char*			doc=NULL;
	FILE*			fd=NULL;
	long			fsize=0;
	char*			ppath=DATADIR "/pixmaps/AspellGUI48.png";

	AboutBoxClass*	about=new AboutBoxClass(window,ppath);

	asprintf(&doc,"%s/docs/gpl-3.0.txt",DATADIR);
	fd=fopen(doc,"r");

	if(fd!=NULL)
		{
			fseek(fd,0,SEEK_END);
			fsize=ftell(fd);
			fseek(fd,0,SEEK_SET);
			licence=(char*)malloc(fsize+1);
			fread(licence,fsize,1,fd);
			fclose(fd);
			licence[fsize]=0;
		}
	about->setLicence(licence);
	about->setAuthors((char*)authors);
	free(doc);
	free(licence);
	about->runAbout();


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
#else

	Qt::WindowFlags flags=window->windowFlags();
    if (((QPushButton*)widget)->isChecked()==true)
	    {
	        window->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	        ((QPushButton*)widget)->setText("Normal");
	        window->show();
	    }
    else
	    {
	        window->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
	         ((QPushButton*)widget)->setText("On-Top");
	       window->show();
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
	Qt::WindowFlags flags;

	window=new QMainWindow;
	window->setWindowTitle("Aspell GUI");
	((QMainWindow*)window)->resize(420,150);
	flags=window->windowFlags();
	window->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	bufferBox=new QPlainTextEdit;
	vlayout->setContentsMargins(0,0,0,0);
	vlayout->addWidget(bufferBox);
	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

//about
	button=new Button("&About");
	hlayout->addWidget(button);
	button->setCallBack((func_ptr)&doAbout);
	button->setIcon(QIcon::fromTheme("help-about"));
//spellcheck //doSpellCheckDoc
	button=new Button("&Spell Check");
	hlayout->addWidget(button);
	button->setCallBack((func_ptr)&doSpellCheckDoc);
	button->setIcon(QIcon::fromTheme("tools-check-spelling"));
//check word
	button=new Button("&Check Word");
	hlayout->addWidget(button);
	button->setCallBack((func_ptr)&checkWord);
	button->setIcon(QIcon::fromTheme("tools-check-spelling"));
//unstick
	button=new Button("&Normal");
	hlayout->addWidget(button);
	button->setCallBack((func_ptr)&doSticky);
	button->setCheckable(true);
	button->setChecked(true);
	
//quit
	button=new Button("&Quit");
	hlayout->addWidget(button);
	button->setCallBack((func_ptr)&doShutdown);
	button->setIcon(QIcon::fromTheme("application-exit"));

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
	gtk_window_set_default_size((GtkWindow*)window,420,150);
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
	char*	labeltext[512];
	int		docflag=documentCheck;

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

void doneDialog(void)
{
	spellCheckWord=NULL;
}

void buildWordCheckQt(int documentCheck)
{
	QVBoxLayout*	vlayout=new QVBoxLayout;
	QWidget*		hbox;
	QHBoxLayout*	hlayout;
	Button*			button;
	char*			labeltext=NULL;
	int				docflag=documentCheck;

	spellCheckWord=new QDialog(window);
	QObject::connect((QDialog*)spellCheckWord,&QDialog::finished,doneDialog);

	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

	asprintf(&labeltext,"Change <i><b>%s</b></i> to: ",badWord);
	badWordLabel=(Widget*)new QLabel(labeltext);
	hlayout->addWidget(badWordLabel);
	wordListDropbox=new QComboBox;
	hlayout->addWidget(wordListDropbox);
	vlayout->addWidget(hbox);

//buttons//doChangeWord
	hlayout=new QHBoxLayout;
	hbox=new QWidget;
	hbox->setLayout(hlayout);

	button=new Button("Apply");
	hlayout->addWidget(button);
	button->setID(docflag);
	button->setCallBack((func_ptr)&doChangeWord);

	button=new Button("Ignore");
	button->setID(1);
	button->setCallBack((func_ptr)&doAddIgnoreWord);
	hlayout->addWidget(button);

	button=new Button("Add");
	button->setID(2);
	button->setCallBack((func_ptr)&doAddIgnoreWord);
	hlayout->addWidget(button);

	button=new Button("Cancel");
	button->setCallBack((func_ptr)&doCancelCheck);
	hlayout->addWidget(button);

	vlayout->addWidget(hbox);

	((QWidget*)spellCheckWord)->setLayout(vlayout);
	((QDialog*)spellCheckWord)->setModal(true);
}
#endif
