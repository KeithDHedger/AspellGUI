/*
 *
 * ©K. D. Hedger. Thu 26 Nov 14:18:32 GMT 2015 keithdhedger@gmail.com

 * This file (main.cpp) is part of AspellGUI.

 * AspellGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * AspellGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with AspellGUI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "globals.h"

#ifndef _USEQT5_
	#include <gtk/gtk.h>
#endif

#include "guis.h"

int main(int argc,char **argv)
{
#ifdef _USEQT5_
	QApplication	app(argc,argv);
#endif
	AspellCanHaveError*	possible_err;

	aspellConfig=new_aspell_config();
	possible_err=new_aspell_speller(aspellConfig);

	if(aspell_error_number(possible_err)!= 0)
		puts(aspell_error_message(possible_err));
	else
		spellChecker=to_aspell_speller(possible_err);

#ifndef _USEQT5_
	gtk_init(&argc,&argv);

	buildMainGuiGtk();
	gtk_window_stick(GTK_WINDOW(window));
	gtk_window_set_keep_above((GtkWindow*)window,true);
	gtk_widget_show_all(window);
	gtk_main();
#else
	holdapp=&app;
	buildMainGuiQt();
	window->show();
	app.exec();
#endif
}