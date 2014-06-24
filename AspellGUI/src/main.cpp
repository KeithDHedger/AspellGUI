/*
 *
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 */

#include "globals.h"

#include "guis.h"

int main(int argc,char **argv)
{
	AspellCanHaveError*	possible_err;
	AspellDictInfoEnumeration * dels;
	const AspellDictInfo * entry;
	AspellDictInfoList * dlist;
	int arraySize;

	gtk_init(&argc,&argv);

	aspellConfig=new_aspell_config();
	possible_err=new_aspell_speller(aspellConfig);

	if(aspell_error_number(possible_err)!= 0)
		puts(aspell_error_message(possible_err));
	else
		spellChecker=to_aspell_speller(possible_err);


	dlist=get_aspell_dict_info_list(aspellConfig);
	dels=aspell_dict_info_list_elements(dlist);
	dictArraySize=0;

	while((entry=aspell_dict_info_enumeration_next(dels))!=0) 
		{
			arraySize=(dictArraySize+1)*sizeof(char*);
			dictArray=(char**)realloc(dictArray,arraySize);
			dictArray[dictArraySize]=strdup(entry->name);
			dictArraySize++;
		}
	delete_aspell_dict_info_enumeration(dels);

	buildMainGui();
	gtk_window_set_default_icon_name(PACKAGE);
	gtk_window_stick(GTK_WINDOW(window));
	gtk_window_set_keep_above((GtkWindow*)window,true);
	gtk_widget_show_all(window);
	gtk_main();
}