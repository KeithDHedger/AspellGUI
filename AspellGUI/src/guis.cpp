/*
 *
 * K.D.Hedger 2013 <kdhedger68713@gmail.com>
 *
*/

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>

#include "config.h"
#include "globals.h"
#include "spellcheck.h"

void doShutdown(GtkWidget* widget,gpointer data)
{
	gtk_main_quit();
}

void doAbout(GtkWidget* widget,gpointer data)
{
	const char*	authors[]={"K.D.Hedger <"MYEMAIL">","\nMore by the same author\n","Xfce4-Composite-Editor\nhttp://gtk-apps.org/content/show.php/Xfce4-Composite-Editor?content=149523\n","KKEdit\nhttp://gtk-apps.org/content/show.php?content=158161\n","Manpage Editor\nhttp://gtk-apps.org/content/show.php?content=160219\n","GtkSu\nhttp://gtk-apps.org/content/show.php?content=158974",NULL};
	const char	copyright[] ="Copyright \xc2\xa9 2013 K.D.Hedger";
	gtk_show_about_dialog(NULL,"authors",authors,"copyright",copyright,"version",VERSION,"website",MYWEBSITE,"program-name","Aspell GUI","logo-icon-name","AspellGUI",NULL); 
}

void buildMainGui(void)
{
	GtkWidget*	vbox;
	GtkWidget*	hbox;
	GtkWidget*	button;
	GtkWidget*	image;

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow*)window,"Aspell GUI");
	gtk_window_set_default_size((GtkWindow*)window,320,60);
	vbox=gtk_vbox_new(false,8);

//text to spell check
	scrollBox=gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	bufferBox=(GtkWidget*)gtk_text_buffer_new(NULL);
	viewBox=(GtkWidget*)gtk_text_view_new_with_buffer((GtkTextBuffer*)bufferBox);
	gtk_text_view_set_wrap_mode((GtkTextView*)viewBox,GTK_WRAP_WORD);
	gtk_container_add(GTK_CONTAINER(scrollBox),(GtkWidget*)viewBox);
	gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)scrollBox);

//buttons
	hbox=gtk_hbox_new(false,8);
	button=gtk_button_new_from_stock(GTK_STOCK_SPELL_CHECK);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doSpellCheckDoc),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);

	image=gtk_image_new_from_stock(GTK_STOCK_SPELL_CHECK,GTK_ICON_SIZE_MENU);
	button=gtk_button_new_with_label("Check Word");
	gtk_button_set_image((GtkButton*)button,image);

	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(checkWord),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);

	button=gtk_button_new_from_stock(GTK_STOCK_ABOUT);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(doAbout),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,4);

	button=gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doShutdown),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);
	gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)hbox);

	g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(doShutdown),NULL);
	gtk_container_add(GTK_CONTAINER(window),(GtkWidget*)vbox);

}

void buildWordCheck(int documentCheck)
{
	GtkWidget*	vbox;
	GtkWidget*	button;
	GtkWidget*	hbox;
	GtkWidget*	label;
	GtkWidget*	image;
	char*		labeltext[512];
	int			docflag=documentCheck;

	spellCheckWord=gtk_dialog_new();
	gtk_window_set_title((GtkWindow*)spellCheckWord,"Spell check word");
	vbox=gtk_vbox_new(true,8);

	hbox=gtk_hbox_new(true,8);

	sprintf((char*)&labeltext,"Change <i><b>%s</b></i> to: ",badWord);
	label=gtk_label_new((char*)&labeltext);
	gtk_label_set_use_markup((GtkLabel*)label,true);
	gtk_box_pack_start(GTK_BOX(hbox),label,true,true,0);

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

	GtkWidget* content=gtk_dialog_get_content_area((GtkDialog *)spellCheckWord);
	gtk_container_add(GTK_CONTAINER(content),(GtkWidget*)vbox);

	gtk_signal_connect_object(GTK_OBJECT(spellCheckWord),"delete_event",GTK_SIGNAL_FUNC(gtk_widget_hide),GTK_OBJECT(spellCheckWord));
	gtk_signal_connect(GTK_OBJECT(spellCheckWord),"delete_event",GTK_SIGNAL_FUNC(gtk_true),NULL);
}





