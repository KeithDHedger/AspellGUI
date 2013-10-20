/*
 *
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include "globals.h"

#include "guis.h"


int main(int argc,char **argv)
{
	gtk_init(&argc,&argv);
//	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(shutdown),NULL);
	buildMainGui();
	gtk_widget_show_all(window);
	gtk_main();
}