/*
 *
 * ©K. D. Hedger. 2015-2026 keithdhedger@gmail.com

 * This file (main.cpp) is part of AspellGUI.

 * AspellGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * AspellGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with AspellGUI.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "globals.h"

int main(int argc,char **argv)
{
	AspellCanHaveError	*possible_err;
	QApplication			app(argc,argv);
	QSettings			prefs("KDHedger","AspellGUI");
	QRect				rg;
	QRect				rf;

	aspellConfig=new_aspell_config();
	possible_err=new_aspell_speller(aspellConfig);

	if(aspell_error_number(possible_err)!= 0)
		puts(aspell_error_message(possible_err));
	else
		spellChecker=to_aspell_speller(possible_err);

	buildMainGuiQt();

	if(argc>1)
		{
			QFile	file(argv[1]);
			if(file.open(QIODevice::ReadOnly | QIODevice::Text))
				{
					QTextStream in(&file);
					bufferBox->setPlainText(in.readAll());
					file.close();
				}
		}

	rg=prefs.value("geometry").toRect();
	window->setGeometry(rg);

	window->show();
	app.exec();

	rg=window->geometry();
	rf=window->frameGeometry();
	rf.setHeight(rf.height()-(rf.height()-rg.height()));
	rf.setWidth(rf.width()-(rf.width()-rg.width()));
	prefs.setValue("geometry",rf);

	delete window;
	delete_aspell_config(aspellConfig);
	delete_aspell_can_have_error(possible_err);
}